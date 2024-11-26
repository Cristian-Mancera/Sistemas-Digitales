# Proyecto de curso Sistemas Digitales
## Resumen
El proyecto busca desarrollar un dispositivo funcional para moderar el ruido en espacios que requieren bajos niveles sonoros, como bibliotecas. Para lograr esto, se utilizan microcontroladores y sensores que permiten medir y alertar cuando los niveles de ruido exceden el límite. El proyecto se divide en varias etapas. En la primera, se investigan las tecnologías actuales que utilizan el Internet de las Cosas (IoT) para controlar el ruido en entornos similares. Esta investigación permite identificar las mejores prácticas y los dispositivos más adecuados para el propósito del proyecto. A continuación, se diseña un prototipo del dispositivo, tomando en cuenta factores como la integración con el entorno y la facilidad de uso. Posteriormente, se procede al ensamblaje y la programación del dispositivo, utilizando microcontroladores y sensores para monitorear y moderar el ruido. En la fase de pruebas, el dispositivo se evalua en condiciones controladas para identificar oportunidades de mejora. A partir de estas pruebas, se optimiza el diseño para asegurar su eficacia en diferentes situaciones. Finalmente, el proyecto busca perfeccionar el dispositivo para que sea confiable, discreto y adaptable a diversas configuraciones de espacios donde se requiera silencio o moderación del ruido.

## ¿Para qué desarrollar un dispositivo de monitoreo y control de ruido?
Las bibliotecas, como espacios destinados a la lectura y el estudio, requieren un ambiente de silencio o, al menos, niveles de ruido moderados para cumplir su propósito. La alta densidad de personas y la falta de consciencia sobre el ruido pueden interferir en la concentración y la efectividad del espacio, afectando negativamente la experiencia de los usuarios y su percepción del valor del lugar.

Por ello, desarrollar un dispositivo que ayude a moderar el ruido en bibliotecas y entornos similares puede tener un impacto positivo, favoreciendo el aprendizaje y la concentración. Este dispositivo debería ser capaz de ayudar a reducir el sonido, integrándose de forma armoniosa con el entorno existente y siendo fácil de usar para no generar inconvenientes adicionales a otros usuarios.

## ¿Porqué este proyecto debe ser tenido en cuenta?
Implementa un dispositivo de moderación de ruido basado en IoT representa una alternativa económica a métodos más costosos, como la remodelación de espacios o el uso de materiales especializados. Al reducir el ruido de manera eficiente sin requerir grandes inversiones, las instituciones pueden optimizar recursos y mejorar el ambiente en lugares como bibliotecas, donde el silencio es esencial para el bienestar de los usuarios, favoreciendo el aprendizaje y la concentración.

Este proyecto no solo aborda un problema práctico en las bibliotecas, sino que también ofrece un valioso ejercicio académico en programación, electrónica e IoT. Además, puede servir como base para futuras investigaciones y mejoras tecnológicas en la gestión del ruido, impactando positivamente en el ámbito educativo y elevando la calidad de vida de los usuarios en espacios compartidos.

## Diseño
Para diseñar el dispositivo, a partir de los requerimientos, habían principalmente 3 problemas a solucionar: cómo medir el sonido, cómo alertar cuando se excede el límite, y cómo comunicarse a internet para enviar la información.
Para dar solución a los primeros dos problemas, una tarjeta Arduino y un par de sensores serían suficientes. Sin embargo, también se necesitaba una tarjeta de red para poder conectarse a internet, así que el ESP32 (que funciona como Arduino con conexión a internet) fue el dispositivo ideal para procesar la información de los sensores y tomar acción.

El circuito del dispositivo tiene un sensor de sonido KY-038 para detectar los niveles de volumen de su entorno, y cuando se supera un límite considerado como el máximo de ruido permitido, se activa un LED y un Buzzer para hacer saber que se debe guardar silencio.

<img src="https://cdn.discordapp.com/attachments/1301778066447536148/1310813471868456982/image.jpg?ex=674695ad&is=6745442d&hm=a5f54861e5143a751bbb81943959f4c583fd6770a567864b7f2e077da2252f8a&" alt="drawing" height="400"/><img src="https://cdn.discordapp.com/attachments/1301778066447536148/1310813456147943475/image.jpg?ex=674695a9&is=67454429&hm=da33914c022ccf72b9929baf636436fa69482ef3f0400908d4e9f8754fe18f6b&" alt="drawing" height="400"/>

## Simulaciones
Las simulaciones se realizaron principalmente con Wokwi, pues es, según su propio eslogan "el simulador de ESP32 más avanzado del mundo", y, en general, funcionó bien para realizar las pruebas antes de llevar los circuitos a la realidad. 

A través de este simulador se realizaron pruebas para probar el funcionamiento y conexión con el controlador del propio circuito, y también fue útil para probar comprender cómo implementar la comunicación a la red con WebSockets. El conocimiento de los recursos disponibles permitió tomar decisiones de cuál sería la mejor forma de solucionar algún requerimiento del proyecto, y hacerlo de la forma más adecuada. 

Dado que en Wokwi no está disponible un sensor de sonido, se utilizó un potenciómetro para simular la señal que puede emitir el sensor a través de su salida análoga. Es decir, que, en el circuito real el potenciómetro sería reemplazado por el sensor de sonido que permite conocer cuál es el nivel de ruido del entorno en que se ubica, lo que es útil para determinar cuánto ruido es suficientemente alto para activar el led, informando que se ha superado el límite de ruido. 

[Proyecto de Wokwi con la simulación del dispositivo](https://wokwi.com/projects/413104915306254337)

## Información ESP32 

<img src="https://cdn.discordapp.com/attachments/1301778066447536148/1310807550622564483/0daed74d-859d-4e43-881f-1e6f70f9f97c.jpg?ex=67469029&is=67453ea9&hm=720dbbb4c27080c4938ac2e65bb409687038a20a38115f27bc8f70ac1abb34da&" alt="drawing" height="400"/><img 


## Conclusiones
- Existen una gran variedad de sensores y también son varias las formas de comunicar la información que estos recolectan hacia diferentes destinos, como servidores web, o incluso otros microcontroladores que estén controlando más sensores.

- Poder compartir la información de los sensores a servidores web permite procesar los datos de acuerdo con los requerimientos, y tomar decisiones a partir de la información disponible, y conectar los componentes a internet permite que un proyecto tenga mayor alcance del que podría tener si se conecta solo a través de medios más limitados, como un cableado, por ejemplo.
