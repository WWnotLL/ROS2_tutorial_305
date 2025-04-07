# ROS2_tutorial_305

<video>https://www.youtube.com/shorts/z_yXPo4au6M<video>

Друзья, всем привет! В этом файлике мы хотим рассказать о своем опыте разработки на ROS2 на примере нашего проекта.

<h3> 
Компоненты, используемые в проекте
</h3>

|№ п.п.| Наименование компонента|Ссылка на компонент|Примерная стоимость (руб.)|
|:-----------|:-----------|:-----------|:-----------|
|1|Одноплатный компьютер |__[Raspberry Pi 4](https://www.ozon.ru/product/raspberry-pi-4-model-b-4gb-ram-mikrokompyuter-1160757800/?at=QktJvgKOQc15kzg8fJggp8MF0PQpzt5J0YLRuR50JEN&keywords=Raspberry+Pi+4)__|8662|
|2|Регулятор напряжения (более известен как понижайка) - 2 шт|__[DC-DC 5A XL4005](https://www.ozon.ru/product/povyshayushchiy-preobrazovatel-napryazheniya-xl6009-dc-dc-reguliruemyy-572176799/?at=08tYNQ9Vxcl3j9xWT3pD3EGsy1YM2sQ8Pk34c1gW3YZ&keywords=DC-DC+5A+XL4005)__|208|
|3|Лидар |__[Xiaomi](https://www.ozon.ru/product/lazernyy-dalnomer-lidar-dlya-robot-pylesosa-xiaomi-viomi-v2-pro-v3-2s-3c-s10-1548926961/?at=w0tglk4KjIR52xWXfnM7qlPtvO8jLmukzWQ37C3qMGVR&keywords=лидар)__|2863|
|4|Ультразвуковой дальномер|__[HC-SR04](https://www.ozon.ru/product/ultrazvukovoy-datchik-rasstoyaniya-hc-sr04-dalnomer-dlya-arduino-stm32-nodemcu-raspberry-982330663/?at=99tr4A6Q0sJJRRKxIxRMVmmCMYoLpyf2J8B1zIQqMLQ6&keywords=HC-SR04)__|174|
|5|Двигатель|__[JGA-370B](https://www.ozon.ru/product/motor-reduktor-jga25-370b-24v-1-226-26-ob-min-1642778442/?at=6WtZL7gzNHEwkKA7C1lKkVPTBzN7mGfMqkMYBtzNAyJ8&keywords=JGA-370B)__|740|
|6|Навигационный модуль|__[Troyka-модуль](https://amperka.ru/product/troyka-accelerometer)__|730|
|7|Колеса для робота - 4 шт|__[Для RC моделей 85мм](https://www.ozon.ru/product/koleso-s-rezinovoy-shinoy-dlya-rc-modeley-avtomobiley-85-mm-1089207812/?utm_medium=organic&utm_source=yandex_serp_products)__|671|
|8|Драйвер для двигателя - 2 шт|__[L298N](https://www.ozon.ru/product/drayver-shagovogo-shchetochnogo-dvigatelya-universalnyy-l298n-1141697851/?at=VvtzqmE3Jf1LkvnXCn3mqPBsoY2vQOi4VNPKosMrQzWX&keywords=Драйвер+для+двигателя+L298N)__|300|
|9|Li-Po аккумулятор|__[ONBO 3300 mAh 45C](https://aliexpress.ru/item/1005005168620074.html?ysclid=m94fjl5jjd958167660&sku_id=12000031952965537)__|2500|
|10|Кнопка/выключатель/тумблер|__[GSMIN KCD11 ON-OFF 3А 250В AC 2pin (15x10)](https://www.ozon.ru/product/tumbler-vyklyuchatel-gsmin-kcd11-on-off-3a-250v-ac-2pin-15x10-krasnyy-953681572/?at=nRtr9g1vEs46WvovfDx6p83hqGJD4OIon5B82TAGNE4M&keywords=тумблер+выключатель)__|91|
|11|Плата|__[Arduino Nano](https://www.ozon.ru/product/arduino-nano-v-3-0-mini-usb-atmega328p-ft232-zapayana-grebenka-arduino-1401642659/?at=ywtAOKQZ1FkKDqrXFYXrDVrT1xvgKoFO2NxloUnNgnLv&keywords=arduino+nano)__|350|
|12|*Набор проводов для пайки|__[24 AWG](https://www.ozon.ru/product/nabor-provodov-dlya-payki-1538619832/?at=57twk3NXxcPmr31VT8w7vnxfkm6zDVCnGMK4jC8kMXxn&from_sku=1538619390&oos_search=false)__|851|
|||Итого|20661|

*Набор проводов пригодится для других проектов<br>
P.S. В данной табличке приведены цены в основном с OZON на случай, если Вам захочется максимально быстро получить компоненты и собрать робота. Для удешевления робота можно покупать компоненты на Aliexpress или Avito. Также важно отметить, что допускается самостоятельная замена компонентов разработчиком из числа имеющихся или, возможно, более дешевых аналогов.<br>
<br>
<br>

# Электрическая схема робота BOX305
![здесь](электрическая%20схема.png?raw=true)

# Инструкция по сборке робота BOX305
## Корпус

Модель корпуса нашего робота выглядит следующим образом 
![здесь](Иллюстрации%20по%20сборке%20робота/06_BOX305_модель%20корпуса.jpg?raw=true) 

Если нет собственных "производственных мощностей", всегда можно воспользоваться услугами __[студий 3D печати](https://uslugi.yandex.ru/213-moscow/category/raznoe/poligraficheskie-uslugi/3dpechat--5635)__

В случае выбора лёгкого пути, смело можно пропускать данный раздел

Для печати корпуса необходим 3D принтер с рабочим полем $200 \times 200$ мм

Выбор материала

Краткая информация об основных видах пластика

| **Параметр**        | **ABS**                                           | **PLA**                                           | **PETG**                                            |
|---------------------|---------------------------------------------------|--------------------------------------------------|----------------------------------------------------|
| **Печать**          | Капризен, требует закрытого бокса и вентиляции   | Очень прост, идеален для новичков                | Умеренно прост, требует настройки                 |
| **Прочность**       | Прочный, ударостойкий                            | Жесткий, но хрупкий при ударе и холоде           | Прочный, гибкий, устойчив к излому                |
| **Темп. стойкость** | Высокая (-40…+80 °C)                             | Низкая (~50 °C, "плывёт" на солнце)              | Средняя (~80 °C), подходит для большинства задач  |
| **Нетоксичность**   | ❌ (выделяет вредные пары)                       | ✅ (безопасен, с запахом жареной еды)             | ✅ (не пахнет, безопасен)                          |

Для нашего робота будем использовать **PETG**

Для печати корпуса воспользуемся специальной программой __[OrcaSlicer](https://orcaslicer.com/)__

Выставим основные параметры печати следующими:

- Температура экструзии — 215-245°C;

- Температура стола — 20-80°C;

- Процент заполнения — 15%;

## Устанока навесных компонентов

1) Начнём с установки двигателей и колёс.

![здесь](Иллюстрации%20по%20сборке%20робота/01_BOX305_разобранный.png?raw=true)

2) Далее монтируем стойки для установки __raspberry 4__, __лидара__, __DC-DC преобразователя__ и __arduino nano__.
3) Подготавливаем крепление для аккумулятора, мы использовали липучки (прямоугольные вырезы на фото ниже).
4) Устанавливаем разьём подключения аккумулятора XT60 и кнопку питания, спаиваем их
5) Далее приступаем к установке драйверов.

![здесь](Иллюстрации%20по%20сборке%20робота/02_BOX305_установка%20драйверов.png?raw=true) 

6) Монтируем arduino и DC-DC преобразователь
7) Настраиваем преобразователь на 5В
8) Припаиваем питание к преобразователю и от него к arduino
9) Протягиваем и припаеваем провода от двигателей к драйверам и arduino
10) Устанавливаем Raspberry

![здесь](Иллюстрации%20по%20сборке%20робота/03_BOX305_установка%20электроники.png?raw=true)

11) Наслаждаемся собранным роботом

![здесь](Иллюстрации%20по%20сборке%20робота/05_BOX305_модель.jpg?raw=true)

![](https://steamuserimages-a.akamaihd.net/ugc/1684895414278596091/26894D3FAAAA36E05F4B46B7DA70819E58BBCCBB/?imw=5000&amp;imh=5000&amp;ima=fit&amp;impolicy=Letterbox&amp;imcolor=%23000000&amp;letterbox=false)
# Инструкция по установке Linux
<br>

В этом курсе мы предлагаем Вам использовать WSL2.<br>
WSL2 - это тип дистрибутива (набора установочных программ) по умолчанию при установке дистрибутива Linux. WSL2 использует технологию виртуализации для запуска ядра Linux в упрощенной служебной виртуальной машине. То есть у вас будет возможность запускать Linux поверх вашем Windows, не устанавливая вторую операционную систему. <br>
становка wsl2 выполнятся на операционных системах Windows 10 и Windows 11. В окне терминала PowerShell или cmd последовательно введите команды (для установки требуется подключение к интернету):<br> 

```
wsl --install
```
```
wsl --set-default-version 2
```
```
wsl --list --online
```
```
wsl --install Ubuntu-22.04
```
```
wsl --install
```

В результате на вашей системе будет установлена wsl2. Для более удобной работы с wsl установим программу `Windows Terminal`<br>
Программа Windows Terminal устанавливается через `Microsoft Store`. В строке поиска Windows напишите `Microsoft Store` и откройте приложение магазина, в поиске магазина напишите `Windows Terminal`. Первый полученный результат будет нужной программой нажмите на результат поиска и нажмите кнопку `"Установить"`.

# Docker. Краткая информация
__Docker__ — это платформа с открытым исходным кодом для автоматизации разработки, доставки и развёртывания приложений.<br>
<br>
__Контейнер в Docker__ — это изолированное пространство, которое позволяет запускать приложения с их зависимостями отдельно от основной системы. В отличие от традиционных виртуальных машин, контейнеры потребляют меньше ресурсов, так как используют ядро основной системы.<br> 
<br>
Установочный файл __[Docker](https://docker.qubitpi.org/desktop/setup/install/windows-install/)__ <br>
Обратите внимание что при установке необходимо обязательно установить опцию `Use the WSL 2 based engine`. <br>
После установки Docker необходимо зайти в настройки<br>
 <br>
 ![Настройки докера](изображения%20к%20тексту/настройки%20докера.png?raw=true)

 <br>
И в пункте `Resources` подпункте `WSL integration` проверить что для вашего дистрибутива интеграция включена.
Для работы в самом симуляторе нам потребуется `IDE VS Code c модулем DEV Containers`. Для установки __[VS Code](https://code.visualstudio.com/)__ скачайте установщик по ссылке и запустите его с параметрами по умолчанию
Для установки расширения необходимо запустить `VS Code` и перейти в раздел `«Расширения»` `(Ctrl+Shift+X)`. В строке поиска введите `“Remote Development”` и установите это расширение.

Для более подробного изучения __[Docker](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/Docker.docx)__ перейдите по ссылке

# __[ROS2](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/ROS2.md)__
# ROS (Robot Operating System)<br>
__Robot Operating System (ROS)__ - это фреймворк (гибкая платформа) для разработки программного обеспечения (ПО) роботов, который ставится на базовую операционную систему, обычно на Linux (Ubuntu).<br>
ROS можно рассматривать, как набор разнообразных инструментов, библиотек и определенных правил, целью которых является упрощение задач разработки ПО роботов.<br>
Он был создан, чтобы стимулировать совместную разработку программного обеспечения робототехники.<br>
Каждая отдельная команда разработчиков и энтузиастов может работать над какой-либо конкретной задачей, но использование единой платформы, позволяет всему сообществу получить и использовать результат их работы для своих личных проектов. <br>
# ROS2 <br>
ROS2 использует те же принципы работы, что и ROS1. В то же время, ROS2 не является частью ROS1. <br>
В отличие от ROS1, cтек которого написан на C++, а клиентские библиотеки на C++ и Python, в ROS2 также используется язык C. <br>
Преимущества использования ROS2: <br>
- позволяет устанавливать безопасные соединения между компонентами системы (нодами);
- взаимодействие осуществляется в режиме «real-time»;
- соединение нескольких роботов в одну сеть упрощен;
- улучшено «качество общения» между нодам (узлами или по простому небольшими командами);<br>

ROS2 реализует real-time взаимодействие через так называемую концепцию DDS (Data Distributed Services) - набор алгоритмов, встраиваемых к разным программам, позволяющий всем программам, имеющим встроенный блок, общаться между собой без центрального сервера.<br>
Для генерации исходного кода для сообщений на разных языках используется протокол ROS MSG. <br>
Для передачи данных между программами существуют следующие инструменты:<br>
1) Топики (topics) – это базовый способ взаимодействия между программами, в этом случае есть программы публикующая (publisher) данные в топик, а есть получающие (subscriber) данные.<br>
Не публикующие и не получающие данные программы ничего не знают об остальных программах, взаимодействующих с топиком. Эта особенность позволяет заменять данные без влияния на другие программы. Например, у нас могут поддерживаться разные инерциальные модули, для каждого из которых существует программа, публикующая данные в один и тот же топик в одном и том же формате.<br>
![image](изображения%20к%20тексту/Топики.jpg?raw=true)

3) __Сервисы__ – это это механизм синхронного (одновременного) или асинхронного (неодновременного, да-да, логично) вызова процедур между нодами. Они позволяют одной ноде вызывать функцию, которая выполняется в другой ноде.<br>
Сервис состоит из двух компонентов:<br>
- __Клиент__ – компонент, формирующий запрос, отправляющий его серверу и ожидающий ответа.<br> 
- __Сервер__ – компонент, получающий запрос, завершающий вычисление и отправляющий ответ клиенту.<br>

Сервисы часто используются для быстрых задач, которые требуют немедленного ответа.<br>
![image](изображения%20к%20тексту/Сервисы.jpg?raw=true)

3) __Действия (Actions)__ — это механизм связи, предназначенный для управления длительными задачами в распределённой робототехнической системе.<br>
Действия состоят из двух компонентов:<br>
__Клиент действия__ — узел, который запрашивает выполнение цели от своего имени. Он ожидает обратной связи и результата по завершении.<br>
__Сервер действий__ — узел, который принимает цель и выполняет необходимые процедуры. Он отправляет обратную связь по мере выполнения действия и возвращает полный результат, когда цель достигнута.<br>
![image](изображения%20к%20тексту/Действия.jpg?raw=true)
![image](изображения%20к%20тексту/компоненты%20действия.png?raw=true)

Дополнительные инструменты, доступные в ROS:
1) __Rqt_gui__ – графический интерфейс представляющий из себя набор плагинов, позволяющий анализировать запущенное окружение ROS.
2) __Node Graph__ – один из плагинов rqt_gui, позволяющий посмотреть запущенные программы и то, как они между собой взаимодействуют.
3) __RVIZ__ – инструмент визуализации стандартных сообщений ROS. 
4) __Nav2__ – набор программ, используемый для навигации робота, его перемещения и предотвращения столкновении.<br><br>

# *Для детального изучения ROS2 рекомендуем пройти __[Народный курс](https://stepik.org/course/221157/syllabus)__*

# Математическая модель пересчета пути
Пересчет пути происходит при помощи колесной одометрии

![](изображения%20к%20тексту/Колесо%20+%20энкодер.png?raw=true)

## Обработка данных с энкодера

Получить пройденное каждым колесом растояние можно по формуле:

$s = \frac{n}{n_{об}} \cdot 2 \pi R$,

где <i>n</i> - количество отсчётов энкодера за время измерения;

$n_{об}$ - количество отсчётов энкодера за 1 оборот колеса;

R - радиус колеса

В свою очередь, поступательная скорость колеса определяется выражением:


$v = \frac{\Delta s}{\Delta t} = \frac{n}{n_{об}} \cdot \frac{2 \pi R}{\Delta t}$,

где $\Delta s$ - путь пройденный за временной интервал $\Delta t$

## Расчёт линейной скорости робота

![](изображения%20к%20тексту/пересчет%20вид%20сверху.png?raw=true)

Средняя поступательная скорость по продольной оси $v_{xc}$ определяется следующим образом:

$v_{xc} = \frac{v_{пл} + v_{ппр} + v_{зл} + v_{зпр}}{4}$

Боковые перемещения для данной конструкции отсутствуют, следовательно скорость по поперечной оси $v_{yc}$ :

$v_{yc} = 0$

## Расчёт угловой скорости

Поворот робота происходит в том случае, когда скорости левых и правых колёс различны. Угловая скорость определяется следующим образом:

$\omega_{zc} = \frac{v_{пр}^{ср} - v_{л}^{ср}}{b/2} = \frac{\frac{v_{ппр} + v_{зпр}}{2} - \frac{v_{пл} + v_{зл}}{2}}{b/2}$

$\omega_{zc} = \frac{(v_{ппр} + v_{зпр}) - (v_{пл} + v_{зл})}{b}$


## Определение положения и ориентации робота

Для определения ориентации в локальной системе координат необходимо проинтегрировать угловую скорость робота $\omega_{zc}$

$\psi = \int \omega_{zc} dt$

Для определения координат по осям необходимо спроецировать скорость на оси локальной системы координат $x и y$ и проинтегрировать по времени

$x = \int v \cdot \cos(\psi) dt$

$y = \int v \cdot \sin(\psi) dt$
