# Инструкция по запуска Docker
<br>
## Дисклеймер
### В основном в этой инструкции будут представлены картинки успешного выполнения команды, в иных случаях будет дано более подробное описание к картинкам
1. Для начала обновите список пакетов и установите обновления:

```
sudo apt update
```

![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/1.png)

```
sudo apt upgrade -y
```

![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/2.png)

Если выполнение программы прошло успешно, то выйдет примерно такое сообщение:
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/3.png)

2. Установите необходимые зависимости
```
sudo apt install -y apt-transport-https ca-certificates curl software-properties-common
```
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/4.png)
3. Добавьте официальный GPG-ключ Docker
```
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
```
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/5.png)
4. Добавьте репозиторий Docker в APT
```
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/6.png)
5. Обновите пакеты и установите Docker
```
sudo apt update
```
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/7.png)
```
sudo apt install -y docker-ce docker-ce-cli containerd.io
```
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/8.png)
6. Проверьте, что Docker работает
```
sudo systemctl status docker
```
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker/Фото%20к%20инструкции/24.png)
8. Проверьте установку
```
docker --version
```
