# ROS2_tutorial_305
![](https://github.com/WWnotLL/ROS2_tutorial_305/blob/main/портрет.jpg)

# Оглавление
- [Компоненты, используемые в проекте](#компоненты-используемые-в-проекте)
- [Электрическая схема робота BOX305](https://github.com/WWnotLL/ROS2_tutorial_305/tree/main/Электроника%20и%20пайка)
- [ROS2](ROS2/README_RO2.md)
- [Docker](Docker/README_Docker%20.md)
- [Установка Linux](Установка%20Linux/README_Linux.md)
- [Инструкция по сборке](Инструкция%20по%20сборке)
- [Математическая модель](Математическая%20модель/README.md)
- [Оживляем робота](Оживляем%20робота)
- [Upgrade'им робота](Upgade'им%20робота)
- [REELS](REELS)
- [Картинки к тексту](изображения%20к%20тексту)

# Компоненты, используемые в проекте
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
