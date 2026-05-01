# Практична робота №9


## Що було зроблено

- Досліджено права доступу до скриптів без права виконання  
- Реалізовано перегляд облікових записів через `getent passwd`  
- Перевірено запуск команд з адміністративними правами через `sudo`  
- Досліджено зміну власника файлу та прав доступу через `chown` і `chmod`  
- Перевірено поточного користувача, UID, GID та список груп через `whoami` і `id`  
- Реалізовано перевірку можливості читання, запису та виконання файлів  
- Досліджено права доступу до домашнього каталогу, `/usr/bin` та `/etc`  
- Створено групу користувачів із повним доступом до окремої директорії  


## Програмні вимоги

- Середовище запуску — термінал Linux Ubuntu  
- Компілятор — GCC  
- Наявність прав `sudo` для виконання адміністративних команд  


## Збірка та запуск

### 1. Перегляд облікових записів 
рограма читає базу даних користувачів через getent passwd і знаходить записи з UID вище заданого порогу. Це дозволяє ідентифікувати звичайних користувачів, окрім поточного.
```
./task9_1
Current user: sasha

Regular users found:
User: nobody, UID: 65534

```
### 2. Доступ до файлу shadow 
Програма виконує команду з підвищеними правами через sudo, що дозволяє отримати доступ до захищеного файлу /etc/shadow, який недоступний звичайному користувачу.
```
./task9_2
fwupd-refresh:!*:20494::::::
saned:!:20494::::::
geoclue:!:20494::::::
cups-browsed:!:20494::::::
hplip:!:20494::::::
gnome-remote-desktop:!*:20494::::::
polkitd:!*:20494::::::
rtkit:!:20494::::::
colord:!:20494::::::
gnome-initial-setup:!:20494::::::
gdm:!:20494::::::
nm-openvpn:!:20494::::::
sasha:$6$8Uj/rNhs6YdjMDUy$O1GIo3fdb8mhO0KWFIS4jGcrYoqtsK0UcOT10TJLwjKY3LoabLUKRRXwUXpDTwWz4Nvfi9FkAO3qk81NFM08A.:20506:0:99999:7:::
vboxadd:!:20506::::::

```
### 3. Копіювання та видалення 
Програма створює файл від імені користувача, копіює його від імені root та перевіряє можливість подальшого редагування і видалення. Це демонструє вплив власника і прав доступу на операції з файлом.
```
./task9_3
File created by regular user.
File copied by root to home directory.
Trying to modify file: Permission denied
File deleted successfully.
```
### 4. Перевірка ідентифікаторів 
Програма виконує команди whoami та id для визначення імені користувача, UID, GID та списку груп, до яких він належить.
```
./task9_4
=== whoami ===
sasha

=== id ===
uid=1000(sasha) gid=1000(sasha) groups=1000(sasha),27(sudo)

```
### 5. Тестування прав 640 
Програма створює файл, змінює його власника і права доступу та перевіряє можливість читання і запису. Це дозволяє дослідити вплив chmod і chown на доступ до файлу.
```
./task9_5
wner root, permissions 644
Read:  yes
Write: no
-rw-rw-rw- 1 root root 50 May  1 15:55 temp_test_file.txt

Owner root, permissions 666
Read:  yes
Write: yes
-r-------- 1 root root 61 May  1 15:55 temp_test_file.txt

Owner root, permissions 400
Read:  no
Write: no
---------- 1 root root 61 May  1 15:55 temp_test_file.txt

Owner root, permissions 000
Read:  no
Write: no

```
### 6. Сканування прав системних файлів
Програма переглядає права доступу до файлів у різних каталогах та перевіряє можливість читання, запису і виконання. Це демонструє обмеження доступу для звичайного користувача.
```
./task9_6
=== Access test for /etc/shadow ===
Read: no
Write: no
Execute: no

=== Trying to read files ===
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
head: cannot open '/etc/shadow' for reading: Permission denied

=== Trying to write files ===
sh: 1: cannot create /etc/passwd: Permission denied
sh: 1: cannot create /usr/bin/ls: Permission denied

=== Trying to execute files ===
/usr/bin/ls executed
cannot execute /etc/passwd

```
### 7. Створення групи користувачів з доступом до певної дерикторії
Створюється група користувачів і директорія з правами доступу лише для цієї групи. Це дозволяє організувати спільний доступ без надання прав кожному користувачу окремо

```
sudo groupadd projectgroup
sudo mkdir /shared_project
sudo chown root:projectgroup /shared_project
sudo chmod 770 /shared_project
sudo usermod -aG projectgroup user1
sudo usermod -aG projectgroup user2
ls -ld /shared_project
drwxrwx--- 2 root projectgroup 4096 May  1 15:45 /shared_project

```
### Висновки

У ході виконання роботи було досліджено механізми керування користувачами, групами та правами доступу в операційній системі Linux.

Було встановлено, що доступ до файлів і директорій визначається комбінацією власника, групи та прав доступу, а також залежить від контексту виконання (звичайний користувач або root).

Практично підтверджено, що підвищення привілеїв через sudo дозволяє виконувати операції, недоступні звичайному користувачу, зокрема доступ до захищених системних файлів.

Дослідження показало, що навіть за відсутності прав на зміну файлу користувач може виконувати інші операції, наприклад видалення, якщо має відповідні права на каталог.
