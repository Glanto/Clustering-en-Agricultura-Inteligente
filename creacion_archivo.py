import serial
import time

# Configura el puerto serial (ajusta el nombre del puerto según sea necesario)
# Verifica el puerto con "ls /dev/tty*" o "dmesg | grep tty"
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

# Espera a que la ESP8266 esté lista
time.sleep(2)

# Abre o crea un archivo CSV
with open("datos.csv", "a") as file:
    file.write("Tiempo,Temperatura,Humedad\n")  # Escribe la cabecera

    try:
        while True:
            if ser.in_waiting > 0:
                # Lee la línea desde el puerto serial
                line = ser.readline().decode('utf-8').strip()
                
                # Verifica si la línea contiene datos válidos
                if line:
                    print(f"Datos recibidos: {line}")
                    # Escribe los datos en el archivo CSV
                    file.write(line + "\n")
                    
            time.sleep(1)  # Ajusta la frecuencia de lectura según sea necesario

    except KeyboardInterrupt:
        print("Lectura interrumpida. Archivo CSV guardado.")

# Cierra el puerto serial
ser.close()
