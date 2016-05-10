# Kompilacja:
./configure && make
# Uruchamianie:
./dhcp_server 

Program wymaga uprawnień root'a
# Konfiguracja
Przed uruchomieniem programu, w pliku config.json należy podać informacje takie jak:
* nazwa interfejsu z którego będzie korzystał serwer
* adres oraz maska sieci w której pracuje serwer
* dane dotyczące pul adresów przydzielanych przez serwer
* maksymalny czas przechowywania informacji o transakcjach
* ścieżka do pliku w którym zapamiętywane są informacje o przydzielonych adresach