from __future__ import print_function
import pixy
from ctypes import *
from pixy import *
import time

# pixy2 Python SWIG get line features example #

get_all_features = True

print("Pixy2 Python SWIG Example -- Get Line Features")

pixy.init ()
pixy.change_prog ("line")

class Vector (Structure):
  _fields_ = [
    ("m_x0", c_uint),
    ("m_y0", c_uint),
    ("m_x1", c_uint),
    ("m_y1", c_uint),
    ("m_index", c_uint),
    ("m_flags", c_uint) ]

class IntersectionLine (Structure):
  _fields_ = [
    ("m_index", c_uint),
    ("m_reserved", c_uint),
    ("m_angle", c_uint) ]

barcodes = BarcodeArray(100)
frame = 0

while 1:
  if get_all_features:
    line_get_all_features ()
  else:
    line_get_main_features ()
  b_count = line_get_barcodes(100, barcodes)
  if b_count > 0:
    print('frame %3d:' % (frame))
    frame = frame + 1
    for index in range (0, b_count):
      print('[BARCODE: X=%d Y=%d CODE=%d]' % (barcodes[index].m_x, barcodes[index].m_y, barcodes[index].m_code))
    time.sleep(1)