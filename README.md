# ESP32

Encuentre toda la información relevante sobre el pinout de ESP32 en una sola página para utilizar correctamente estos pines GPIO para su proyecto de electrónica de bricolaje. Aunque existen muchas variaciones de placas ESP32, la función de los pines sigue siendo la misma. Sin embargo, es posible que algunos pines no estén disponibles, según su modelo.

Hay muchas placas ESP32 con diferentes disposiciones de pines. Aquí hay un diagrama de pines detallado de 2 placas ESP32 diferentes. Será beneficioso conocer las funciones específicas de cada pin:

## Board

![Texto del enlace](/Doc/esp32.png)


# Pines de alimentación

Los pines de alimentación proporcionan el voltaje necesario al módulo para funcionar:

3V3 es el pin de voltaje de suministro principal. Debe contar con una fuente de alimentación estable de 3,3 V. GND es el pin de tierra.

![Texto del enlace](/Doc/esp32-pwr.png)

# Pin Habilitar (Enable)

El pin EN es el pin de habilitación para el ESP32. Cuando se coloca en ALTO, el chip está habilitado y operativo; cuando se baja, el chip se desactiva


![Texto del enlace](/Doc/esp32-enable.png)

## Pines GPIO

El módulo ESP32-WROOM-32 tiene 32 pines GPIO a los que se les pueden asignar diferentes funciones programando los registros apropiados. Hay varios tipos de GPIO: solo digitales, analógicos, capacitivos táctiles, etc. La mayoría de los GPIO digitales se pueden configurar con pull-up o pull-down interno, o configurarse en alta impedancia.

![Texto del enlace](/Doc/esp32-gpio.png)


## ¿Qué GPIO son seguros de usar?

Aunque el módulo tiene muchos pines con diversas funciones, es posible que algunos de ellos no sean adecuados para sus proyectos. La siguiente tabla muestra qué pines son seguros de usar y cuáles deben usarse con precaución.

Green -  Son perfectamente seguros de usar.
Yellow - Preste mucha atención porque su comportamiento, especialmente durante el arranque, puede ser impredecible. Úsalos sólo cuando sea absolutamente necesario.
Red - No son seguros para usar.

La siguiente imagen muestra qué pines GPIO se pueden utilizar de forma segura.

![Texto del enlace](/Doc/esp32-gpio-secure.png)


## GPIO de entrada únicamente

Los pines 4, 5, 6 y 7 no se pueden configurar como salidas. Se pueden utilizar como entradas digitales o analógicas, o para otros fines. También carecen de resistencias internas pull-up y pull-down, a diferencia de los otros pines GPIO.

## Pines de interrupción ESP32

Todos los GPIO se pueden configurar como interrupciones.


Pines ADC

El módulo ESP32-WROOM-32 tiene dos bloques ADC (Convertidor analógico a digital); ADC1 y ADC2. Cada bloque tiene múltiples canales:


ADC1: contiene 6 canales (etiquetados como ADC1_CH0 y ADC1_CH3 a ADC1_CH7).
ADC2: contiene 10 canales (etiquetados como ADC2_CH0 a ADC2_CH9).

![Texto del enlace](/Doc/esp32-adc.png)


La resolución de los ADC en el ESP32 se puede configurar hasta 12 bits. Esto significa que el ADC puede detectar 4096 (2^12) niveles analógicos discretos. Esto da como resultado una resolución de 3,3 V (voltaje de funcionamiento)/4096 unidades, o 0,0008 voltios (0,8 mV) por unidad.

#### Cuando Wi-Fi está habilitado, los pines ADC2 no se pueden usar. Si necesita Wi-Fi, considere usar los pines ADC1.


## Pines DAC

El módulo ESP32-WROOM-32 contiene dos convertidores digitales a analógicos (DAC) de 8 bits. Estos DAC son útiles para convertir señales digitales en voltajes analógicos.

![Texto del enlace](/Doc/esp32-dac.png)


# Pines táctiles

El módulo ESP32-WROOM-32 tiene diez GPIO capacitivos táctiles etiquetados como TOUCH0 a TOUCH9. Estos pines funcionan midiendo el cambio en la capacitancia cuando un dedo u objeto conductor está cerca de la superficie del pin.

Se pueden utilizar para diversas aplicaciones, como botones táctiles, controles deslizantes táctiles o incluso reconocimiento de gestos básico. También se pueden usar para despertar el ESP32 del sueño profundo , lo cual es particularmente útil en aplicaciones sensibles a la energía.

![Texto del enlace](/Doc/esp32-tactico.png)

# Pines I2C
El módulo ESP32-WROOM-32 tiene dos interfaces de bus I2C, pero no tiene pines I2C dedicados. En cambio, permite una asignación de pines flexible, lo que significa que cualquier pin GPIO se puede configurar como I2C SDA (línea de datos) y SCL (línea de reloj).

Sin embargo, GPIO21 (SDA) y GPIO22 (SCL) se usan comúnmente como pines I2C predeterminados para facilitar el uso de códigos, bibliotecas y bocetos de Arduino existentes.

![Texto del enlace](/Doc/esp32-i2c.png)

# Pines SPI

El módulo ESP32-WROOM-32 presenta tres SPI (SPI, HSPI y VSPI). HSPI y VSPI se usan comúnmente para propósitos generales, mientras que el tercero se usa para interactuar con la memoria flash SPI integrada en el módulo.

Similar a I2C, el ESP32 permite una asignación flexible de pines para SPI. Esto significa que cualquier pin GPIO se puede configurar como pin SPI

![Texto del enlace](/Doc/esp32-spi.png)

# Pines UART

El módulo ESP32-WROOM-32 tiene tres interfaces UART: UART0, UART1 y UART2. Estas interfaces permiten la comunicación en serie con varios periféricos o para fines de registro y depuración.


![Texto del enlace](/Doc/esp32-uart.png)


Tengan en cuenta que los pines UART1 (GPIO 9 y GPIO 10) se utilizan para interactuar con la memoria flash SPI integrada en el módulo, por lo que no puede utilizarlos. Sin embargo, aún puedes usar UART1 activando bits el protocolo UART en otros pines GPIO.


Los pines TX y RX básicos, las interfaces UART en el ESP32 también admiten RTS (Solicitud de envío) y CTS (Borrar para enviar) para el control de flujo de hardware, aunque se usan con menos frecuencia.


# Pines PWM

Casi todos los pines GPIO del módulo se pueden configurar para generar salida PWM.

![Texto del enlace](/Doc/esp32-pwm.png)

El PWM en el ESP32 se puede configurar con alta resolución, generalmente hasta 16 bits, lo que permite un control preciso sobre las señales PWM. La frecuencia PWM también se puede ajustar, con un rango típico de unos pocos Hz a decenas de MHz, lo que la hace adecuada para una amplia gama de aplicaciones, desde controlar motores hasta atenuar LED.

# Pines GPIO RTC

Algunos GPIO se enrutan al subsistema de bajo consumo RTC y se conocen como RTC GPIO. Estos GPIO se pueden utilizar para despertar el ESP32 del sleep y para interactuar con periféricos RTC.

![Texto del enlace](/Doc/esp32-rtc.png)






