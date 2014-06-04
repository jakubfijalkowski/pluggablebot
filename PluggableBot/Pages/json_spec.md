Struktury JSON                                                                              {#pages_json_spec}
==============

PluggableBot używa formatu JSON do obsługi plików konfiguracyjnych i jak jednego
z formatów odpowiedzi do użytkownika(do włączenia w pliku konfiguracyjnym).
Pełną dokumentację formatu JSON można znaleźć pod adresem http://www.json.org/json-pl.html.

## Używane oznaczenia ##

Struktura plików JSON jest przedstawiona jako wielopoziomowe listy, gdzie każdy element
listy oznacza pewien element pliku JSON.

## Plik konfiguracyjny ##

- *pluginsPath* - opcjonalne, domyślnie *Plugins* - ścieżka do katalogu z wtyczkami.
- *sendJSON* - opcjonalne, domyślnie *false* - *true* / *false* - określa, czy użytkownik
  dostanie odpowiedź jako JSON, czy jako zwykłą wiadomość.

Kolejnymi elementami są konfiguracje poszczególnych wtyczek:

- *DefaultProtocols*
  * *gg* - ustawienia protokołu Gadu-Gadu
    - *number* - numer konta, do którego aplikacja powinna się zalogować
    - *password* - hasło do w/w konta.
    - *contacts* - opcjonalne, domyślnie pusta - tabela numerów, które powinny być
      zgłoszone jako lista kontaktów.
    - *status* - opcjonalne, domyślnie 2 - status konta po zalogowaniu
      Możliwe wartości:
      * 2 - dostępny,
      * 4 - dostępny, z opisem,
      * 3 - zajęty,
      * 5 - zajęty z opisem,
      * 20 - niewidoczny,
      * 21 - niewidoczny, z opisem
      * 23 - *pogadam*,
      * 24 - *pogadam*, z opisem,
      * 33 - *nie przeszkadzać*
      * 34 - *nie przeszkadzać*, z opisem
    - *statusDescription* - opcjonalne, domyślnie puste - jeśli *status* zawiera
      status z opisem, pole to określa właśnie opis.

## Odpowiedź do użytkownika ##

Jeśli *sendJSON* jest ustawione na *true*, użytkownik otrzyma odpowiedź w formacie
JSON.

- *isAsync* - *true* / *false* - określa, czy odpowiedź jest synchroniczna czy
  asynchroniczna.
- *isError* - *true* / *false* - określa, czy komenda wykonała się prawidłowo.
- *isAsyncResponse* - *true* / *false* -  mówi, czy jest to odpowiedź na asynchroniczne
  wykonanie komendy, czy nie.
- *command* - opcjonalne, domyślne puste - określa nazwę komendy, do wywołania której
  to jest odpowiedź. Niepuste tylko, gdy *isAsyncResponse* jest *true*.
- *message* - wiadomość tekstowa, która zwrócona by była użytkownikowi, gdyby
  *sendJSON* było *false*(może być wiadomością o błędzie).
- *additionalData* - opcjonalne, obiekt - dodatkowe dane w formacie JSON zwrócone
  przez komendę.
- *systemError* - obecne, gdy *isError* = *true* - numer błędu systemowego.
- *systemMessage* - obecne, gdy *isError* = *true* - wiadomość opisująca w/w błąd.
