#%% [markdown]
# # Testing model on MCU
# ### Import TensorFlow into your program:
# code reference\
# [TensorFlow 2 quickstart for beginners](https://www.tensorflow.org/tutorials/quickstart/beginner)
# [TensorFlow 2 quickstart for experts](https://www.tensorflow.org/tutorials/quickstart/advanced)
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.utils import plot_model
import numpy as np
from sklearn.metrics import accuracy_score

from serial import Serial
import struct

import matplotlib.pyplot as plt

print("TensorFlow version:", tf.__version__)
MCU_COM = 'COM3'
baudrate = 115200

# %% [markdown]
# ### Load and prepare the MNIST dataset.
mnist = tf.keras.datasets.mnist

(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train, x_test = x_train / 255.0, x_test / 255.0

# Add a channels dimension
x_train = x_train[..., tf.newaxis].astype("float32")
x_test = x_test[..., tf.newaxis].astype("float32")
plt.figure()
for i in range (25):
  plt.subplot(5,5,i+1)
  plt.xticks([])
  plt.yticks([])
  plt.imshow(x_train[i,:,:], cmap=plt.cm.gray)
plt.show()

#%% [markdown]
# ### Define function for send data to MCU
def get_pack_format(data):
    if type(data) is np.short:
        return b'h'
    if type(data) is np.float32:
        return b'f'
    if type(data) is bytes:
        return b's'
    if type(data) is np.float64:
        return b'd'
    raise ValueError(f'{type(data)} not define')

def serial_send_data(serial, send_data, com=MCU_COM, baudrate=115200, timeout=0.1):
    send_pack=[]
    pack_format = get_pack_format(send_data[0])
    for d in send_data:
        send_pack += list(struct.pack(pack_format, d))
    size = len(send_pack)
    size_pack = struct.pack(b'H', size)
    serial.write(size_pack)
    serial.write(bytes(send_pack))

def send_packet_to_MCU(serial, id, data):
    serial.write(id)
    serial_send_data(serial, data)
       
def send_Img_to_MCU(ser, img):
    img = img.reshape(img.size)
    send_packet_to_MCU(ser, b'I', img)

def get_mcu_predict(serial):
    predict = serial.read(2)
    predict  = struct.unpack(b'H', predict)[0]

    duration = serial.read(2)
    duration  = struct.unpack(b'H', duration)[0]
    return predict, duration

#%% [markdown]
# ### Testing on MCU
plt.figure()
for i in range (25):
    test_img = x_test[i,:,:]
    ground_true = y_test[i]
    plt.subplot(5,5,i+1)
    plt.xticks([])
    plt.yticks([])
    plt.imshow(test_img, cmap=plt.cm.gray)
    with Serial(MCU_COM, baudrate, timeout=1) as ser:
        send_Img_to_MCU(ser, test_img) 
        predict, duration = get_mcu_predict(ser)
    print(f'Ground True: {ground_true} | Predict: {predict} | Duration: {duration}us')

#%% [markdown]
# ### Evaluate MCU Classification Performance
y_pred = []
for x in x_test[:2500]:
    with Serial(MCU_COM, baudrate, timeout=1) as ser:
        send_Img_to_MCU(ser, x) 
        predict, duration = get_mcu_predict(ser)
    y_pred.append(predict)
    # print(f'Ground True: {ground_true} | Predict: {predict} | Duration: {duration}us')

y_pred = np.array(y_pred)
model_acc = accuracy_score(y_test[:2500], y_pred)
print(f'accuracy={model_acc}')