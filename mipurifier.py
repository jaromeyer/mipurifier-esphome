import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200)
pwr = 0
changed = False
while(True):
  line = ser.read_until(b'\r')[:-1].decode()
  tokens = line.split()
  #print('received: ', line)
  if tokens[0] == 'net':
    ser.write(b'cloud')
  elif tokens[0] == 'properties_changed':
    #print('property', tokens[1], tokens[2], 'set to', tokens[3])
    id = int(tokens[1] + tokens[2])
    if id == 81:
      # Button pressed
      if tokens[3] == '"power"':
        print('Front button pressed')
      elif tokens[3] == '"led"':
        print('Back button pressed')
        # cycle manual power levels
        pwr = (pwr+1)%15
        changed = True
    elif id == 36:
      print('Air quality:', tokens[3])
    elif id == 37:
      print('Humidity:', tokens[3])
    elif id == 38:
      print('Temperature:', tokens[3])
    elif id == 43:
      print('Filter:', tokens[3])
    elif id == 25:
      val = int(tokens[3])
      if val == 0:
        print('Mode: auto')
      elif val == 1:
        print('Mode: sleep')
      elif val == 2:
        print('Mode: manual')
      elif val == 3:
        print('Mode: levels')
    elif id == 1510:
      val = int(tokens[3])
      if val == 1:
        print('Level: low')
      elif val == 2:
        print('Level: medium')
      elif val == 3:
        print('Level: high')
    elif id == 22:
      if tokens[3] == 'true':
        print('Turned on')
      else:
        print('Turned off')
    ser.write(b'ok\r')
  elif tokens[0] == 'time':
    ser.write(str(int(time.time())).encode())
  elif tokens[0] == 'get_down':
    if changed:
      ser.write(('down set_properties 10 10 ' + str(pwr)).encode())
      changed = False
    else:
      ser.write(b'down none')
  else:
    ser.write(b'ok')