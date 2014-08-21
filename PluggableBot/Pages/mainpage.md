PluggableBot - dokumentacja                                                                 {#mainpage}
===========================

## Informacje wstępne ##
Celem projektu jest stworzenie autonomicznego programu, który po wstępnej konfiguracji
będzie potrafił automatycznie odpowiadać na określoną listę komend otrzymywanych przez
protokoły komunikacji sieciowej(np. Gadu-Gadu, XMPP). Założeniem głównym jest takie
zaprojektowanie architektury aplikacji, by była ona możliwie najbardziej elastyczna. Ma
pozwalać na łatwe dodawanie nowych komend, obsługi protokołów i wymiany części głównej
aplikacji. 

## Definicje ##
### JSON ###
JavaScript Object Notation – tekstowy format wymiany danych. Strona projektu oraz
dokumentacja: http://www.json.org/json-pl.html.

### Protokół komunikacji sieciowej ###
Zbiór ścisłych reguł i kroków postępowania, które są automatycznie wykonywane w celu
nawiązania łączności i wymiany danych(tutaj – tekstowych) między klientem(użytkownikiem)
a serwerem.

### Wiadomość użytkownika ###
Jest to ciąg znaków otrzymywany od określonego użytkownika z wykorzystaniem protokołu
komunikacji sieciowej.

### Komenda ###
Akcja, która powinna zostać wykonana, gdy wiadomość pasuje do wzorca unikalnego dla danej
komendy Wyróżniamy dwa rodzaje komend: 
* Pełno tekstowe – komenda nie ma wyróżnionych części i składa się z 
  interpretowanej całościowo.
* Zwykłe – analogicznie do komend wiersza poleceń CMD, czy powłok Uniksowych – komenda
  składa się z nazwy polecenia(składającej się ze znaków alfanumerycznych oraz podkreślenia)
  oraz opcjonalnych argumentów w postaci nazwa = wartość, gdzie nazwa jest ciągiem znaków
  alfanumerycznych oraz podkreśleń, a wartość jest dowolnym wyrażeniem. Wartość parametru
  może być zawarta w znakach cudzysłowu, dla zachowania białych znaków.

Więcej informacji znajduje się w dokumentacji
[ICommandExecutor](@ref PluggableBot::Commands::ICommandExecutor) oraz
[IParser](@ref PluggableBot::Commands::IParser).

### Wtyczka ###
Jest to program rozszerzający funkcjonalność aplikacji, ale niebędący jej integralną częścią.
Musi udostępniać pewien ściśle określony interfejs komunikacji. Głównie rozpowszechniany,
jako biblioteka ładowana dynamicznie(DLL). Wyróżniamy następujące rodzaje wtyczek:
* Obsługujący protokół – dodaje do programu obsługę protokołu komunikacji sieciowej.
* Obsługujący komendy – dodaje do programu obsługę nowych komend.

Więcej informacji znajduje się w dokumentacji [IPlugin](@ref PluggableBot::Plugins::IPlugin)
oraz [PluginManager](@ref PluggableBot::Plugins::PluginManager).

### Komunikaty/wiadomości aplikacji ###
Aplikacja do komunikacji między poszczególnymi podsystemami używa mechanizmu
wiadomości/komunikatów(pojęcia używane wymiennie w niniejszym dokumencie), przesyłanych pomiędzy
wątkami z wykorzystaniem kolejki wiadomości(lub bardzo uproszczonego wzorca szyny wiadomości).
Komunikat taki to dowolny obiekt, który ma określony numeryczny typ(unikalny dla konkretnego
typu wiadomości) oraz dziedziczy z określonego interfejsu
([IMessage](@ref PluggableBot::Messaging::IMessage)). 

## Obsługiwane protokoł ##
W aktualnej wersji aplikacja obsługuje następujące protokoły:
* Gadu-Gadu - z wykorzystaniem wtyczki [DefaultProtocols](@ref PluggableBot::DefaultProtocols).

## Obsługiwane komendy ##
W aktualnej wersji aplikacja posiada dwie domyślne wtyczki obsługujące komendy:
* [StatelessCommands](@ref PluggableBot::StatelessCommands) z komendami:
  - [HelpCommand](@ref PluggableBot::StatelessCommands::HelpCommand)
  - [ListProtocolsCommand](@ref PluggableBot::StatelessCommands::ListProtocolsCommand)
  - [PingCommand](@ref PluggableBot::StatelessCommands::PingCommand)
  - [SendCommand](@ref PluggableBot::StatelessCommands::SendCommand)
  - [StopCommand](@ref PluggableBot::StatelessCommands::StopCommand)
* [FilesystemPlugin](@ref PluggableBot::FilesystemPlugin) z komendami:
  - [PwdCommand](@ref PluggableBot::FilesystemPlugin::PwdCommand)
  - [CdCommand](@ref PluggableBot::FilesystemPlugin::CdCommand)
  - [LsCommand](@ref PluggableBot::FilesystemPlugin::LsCommand)
  - [MvCommand](@ref PluggableBot::FilesystemPlugin::MvCommand)
  - [RmCommand](@ref PluggableBot::FilesystemPlugin::RmCommand)
  - [CatCommand](@ref PluggableBot::FilesystemPlugin::CatCommand)
  - [StoreTextCommand](@ref PluggableBot::FilesystemPlugin::StoreTextCommand)
  - [StoreImageCommand](@ref PluggableBot::FilesystemPlugin::StoreImageCommand)

## Działanie aplikacji ##
Właściwym punktem wejścia aplikacji jest klasa [Application](@ref PluggableBot::Application),
której dokładny opis znajduje się na [osobnej stronie](@ref pages_application_description).
Jest to też dobry punkt wejścia, do rozpoczęcia czytania aplikacji.

## Zobacz również ##
* [Opis głównego obiektu aplikacji](@ref pages_application_description)
* [Struktury JSON](@ref pages_json_spec)
* [Wtyczka DefaultProtocols](@ref PluggableBot::DefaultProtocols)
* [Wtyczka StatelessCommands](@ref PluggableBot::StatelessCommands)
* [Wtyczka FilesystemPlugin](@ref PluggableBot::FilesystemPlugin)