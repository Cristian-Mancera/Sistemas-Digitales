## Introducción  

El presente proyecto tiene como objetivo diseñar y desarrollar un dispositivo funcional que permita moderar los niveles de ruido en espacios donde se requiere un ambiente silencioso, como bibliotecas. Este sistema utiliza tecnologías basadas en el Internet de las Cosas (IoT), microcontroladores y sensores, con el propósito de medir y reducir el ruido de manera eficiente.  

El desarrollo se estructuró en varias fases. Inicialmente, se investigaron las tecnologías actuales que aplican IoT para la gestión del ruido en entornos similares, identificando las mejores prácticas y dispositivos más adecuados. Posteriormente, se diseñó un prototipo que considera factores como la integración en el entorno y la facilidad de uso. Este prototipo fue ensamblado y programado para realizar pruebas en condiciones controladas, detectando oportunidades de mejora y optimizando su diseño. El resultado es un dispositivo confiable, discreto y adaptable a diferentes configuraciones.  



## Objetivos  

1. Investigar métodos actuales que emplean IoT para reducir el ruido en entornos que lo requieren.  
2. Diseñar un prototipo eficiente que permita moderar el ruido en espacios específicos.  
3. Construir el dispositivo integrando microcontroladores y sensores necesarios para su funcionalidad.  



## Justificación  

Implementar un dispositivo de moderación de ruido basado en IoT representa una alternativa accesible frente a métodos convencionales, como remodelaciones estructurales o el uso de materiales especializados para absorción acústica. Este enfoque no solo optimiza los recursos económicos, sino que también mejora la calidad del ambiente sin inversiones costosas.  

En lugares como las bibliotecas, donde el silencio es esencial para la concentración y el aprendizaje, el proyecto busca ofrecer un entorno más favorable para los usuarios. Asimismo, fomenta la convivencia en espacios compartidos, mejorando la experiencia general.  

Desde un enfoque académico, este proyecto combina conocimientos en programación, electrónica e IoT, sirviendo como base para futuras investigaciones en el control de ruido.  



## Metodología  

1. **Investigación:** Se analizaron los protocolos actuales en bibliotecas mediante entrevistas al personal para entender sus estrategias de manejo del ruido.  
2. **Diseño:** Se desarrolló un plano preliminar del dispositivo y su funcionamiento, incorporando los hallazgos de la investigación.  
3. **Simulación:** Se probaron diferentes configuraciones mediante herramientas como Wokwi, ajustando la sensibilidad del sensor y la respuesta del ESP32.  
4. **Implementación:** Se ensambló el prototipo físico, utilizando componentes como el microcontrolador ESP32 y un sensor de sonido.  
5. **Pruebas:** El dispositivo fue evaluado en una biblioteca para identificar áreas de mejora.  
6. **Optimización:** Basándose en los resultados de las pruebas, se ajustaron elementos para mejorar la eficiencia y discreción del dispositivo.  



## Materiales  

- ESP32 (Microcontrolador)  
- Sensor de Sonido Small Sound  
- Buzzer  
- Protoboard  
- LEDs  
- Resistencias  
- Jumpers  
- Caja de ensamblaje para el diseño final  


## Diseño  

Para diseñar el dispositivo, a partir de los requerimientos, había principalmente 3 problemas a solucionar: cómo medir el sonido, cómo alertar cuando se excede el límite, y cómo comunicarse a internet para enviar la información.  

Para dar solución a los primeros dos problemas, una tarjeta Arduino y un par de sensores serían suficientes. Sin embargo, también se necesitaba una tarjeta de red para poder conectarse a internet, así que el ESP32 (que funciona como Arduino con conexión a internet) fue el dispositivo ideal para procesar la información de los sensores y tomar acción.  

El circuito del dispositivo tiene un sensor de sonido KY-038 para detectar los niveles de volumen de su entorno, y cuando se supera un límite considerado como el máximo de ruido permitido, se activa un LED y un Buzzer para hacer saber que se debe guardar silencio.

[Imagen 1: Prototipo inicial]

![**Imagen 1:** Prototipo inicial](https://cdn.discordapp.com/attachments/1301778066447536148/1310813456147943475/image.jpg?ex=674938a9&is=6747e729&hm=1c935ee92d1bbe4ac83b23d4752fb19fb66e5046d7c1fe856e812460bb8548c7&)


## Simulaciones y Pruebas  

Las simulaciones se llevaron a cabo en **Wokwi**, un simulador avanzado para ESP32. Esta herramienta permitió realizar pruebas preliminares antes de implementar los circuitos físicamente, incluyendo la simulación de conexiones y comunicación en red mediante WebSockets.  

Dado que Wokwi no cuenta con un sensor de sonido en su librería, se utilizó un potenciómetro para simular la señal analógica que este generaría. En el circuito final, el potenciómetro fue reemplazado por el sensor real, que detecta los niveles de ruido del entorno. Esto permitió determinar umbrales de activación para los LEDs, indicando cuándo el nivel de ruido excedía los límites establecidos.  

Este proceso de simulación y pruebas asegura que el diseño propuesto cumpla con los requerimientos del proyecto y sea capaz de operar de forma efectiva en un entorno real.


[Proyecto de Wokwi con la simulación del dispositivo](https://wokwi.com/projects/413104915306254337)

## Información ESP32 

<img src="https://cdn.discordapp.com/attachments/1301778066447536148/1310807550622564483/0daed74d-859d-4e43-881f-1e6f70f9f97c.jpg?ex=67469029&is=67453ea9&hm=720dbbb4c27080c4938ac2e65bb409687038a20a38115f27bc8f70ac1abb34da&" alt="drawing" height="400"/><img 


## Conclusiones  

1. **Viabilidad del proyecto:** El prototipo desarrollado demostró que es posible implementar una solución basada en IoT para moderar el ruido en entornos silenciosos sin necesidad de grandes inversiones en infraestructura.  

2. **Eficiencia del diseño:** A través de simulaciones y pruebas físicas, se validó que el dispositivo puede detectar y responder a niveles de ruido altos con precisión. El uso del microcontrolador ESP32 junto con un sensor de sonido resultó ser una combinación eficiente y de bajo costo.  

3. **Flexibilidad y adaptabilidad:** El diseño modular del dispositivo permite su implementación en una variedad de espacios, desde bibliotecas hasta oficinas o incluso hogares, adaptándose fácilmente a las necesidades específicas de cada entorno.  

4. **Fomento de la convivencia:** Este dispositivo contribuye a mejorar el ambiente en espacios compartidos, promoviendo la convivencia respetuosa y ayudando a mantener condiciones propicias para la concentración y el aprendizaje.  

5. **Impacto académico:** La ejecución del proyecto permitió aplicar conocimientos en electrónica, programación e IoT, demostrando su relevancia práctica y ofreciendo una base sólida para proyectos futuros en gestión acústica.  

6. **Sostenibilidad:** Este tipo de solución promueve la sostenibilidad al ofrecer un método eficiente para controlar el ruido, evitando remodelaciones o soluciones de mayor impacto ambiental y económico.  

7. **Identificación de áreas de mejora:** Las pruebas realizadas mostraron oportunidades de optimización, como ajustar la sensibilidad del sensor para ambientes con diferentes niveles de ruido base y mejorar la integración del diseño físico para que sea más discreto.  

8. **Escalabilidad del proyecto:** El dispositivo tiene potencial para ser mejorado y escalado mediante la incorporación de funcionalidades adicionales, como monitoreo remoto a través de aplicaciones móviles o sistemas de alerta avanzados, lo que abre posibilidades para su comercialización o implementación en proyectos más amplios.  

9. **Uso educativo:** Además de ser una solución práctica, el dispositivo puede ser utilizado como herramienta didáctica para enseñar conceptos de IoT, electrónica y diseño de sistemas embebidos, especialmente en instituciones académicas.  

10. **Contribución al bienestar:** La moderación del ruido en espacios compartidos mejora significativamente la experiencia de los usuarios, impactando positivamente en su bienestar emocional y su productividad.

[**Imagen 3:** Prototipo final entregado]  
<video width="640" height="360" controls>
  <source src="Media/PROTOTIPO_FINAL.mp4" type="video/mp4">
  Tu navegador no soporta el elemento de video.
</video>




