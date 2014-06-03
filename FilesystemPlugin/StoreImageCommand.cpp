#include "StoreImageCommand.h"
#include <Shlwapi.h>
#include <fstream>
#include <PluggableBot/Exceptions/ExecutionException.h>
#include <PluggableBot/Messages/Messages.h>
#include "Helper.h"

namespace PluggableBot
{
	namespace FilesystemPlugin
	{

		const std::string InvalidPath = "ścieżka jest nieprawidłowa.";
		const std::string PathIsNotFile = "nie można nadpisać zawartości folderu";
		const std::string CannotWriteToFile = "nie udało się zapisać pliku";
		const std::string NoImage = "nie wysłano obrazka. Obrazek musi być wysłany przed wysłaniem komendy StoreText";
		const std::string FileWritten = "Plik został zapisany.";

		StoreImageCommand::StoreImageCommand(ApplicationContext* context)
			: ICommand("storeimage"), context(context), matcher(new SimpleMatcher("storeimage", { "file" }))
		{ }

		const IMatcher* StoreImageCommand::GetMatcher() const
		{
			return this->matcher.get();
		}

		CommandExecutionResults StoreImageCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			auto path = SanitizePath(context.ParseResults->GetParameter("file"));
			auto newPath = JoinPath(currentDir, path);
			if (newPath.empty())
			{
				throw Exceptions::ExecutionException(InvalidPath);
			}
			if (PathIsDirectoryA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(PathIsNotFile);
			}

			auto imageList = this->context->Messenger->TryGet([&](Messaging::IMessage* message)
			{
				return $MessageIs(Messages::ImageReceived) &&
					((Messages::ImageReceived*)message)->Sender == context.Message->Sender &&
					((Messages::ImageReceived*)message)->Protocol == context.Message->SourceProtocol;
			});
			if (imageList->empty())
			{
				throw Exceptions::ExecutionException(NoImage);
			}
			Messages::ImageReceived* image = (Messages::ImageReceived*)imageList->front().get();

			std::ofstream file(newPath, std::ios_base::binary | std::ios_base::trunc);
			file.write(image->Data.get(), image->DataSize);
			if (!file)
			{
				throw Exceptions::ExecutionException(CannotWriteToFile);
			}
			return CommandExecutionResults(FileWritten);
		}

	}
}
