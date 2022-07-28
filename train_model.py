#%% [markdown]
# # Traing NNIST Classifier
# ### Import TensorFlow into your program:
# code reference\
# [TensorFlow 2 quickstart for beginners](https://www.tensorflow.org/tutorials/quickstart/beginner)
# [TensorFlow 2 quickstart for experts](https://www.tensorflow.org/tutorials/quickstart/advanced)

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.utils import plot_model

import matplotlib.pyplot as plt

print("TensorFlow version:", tf.__version__)
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
# ### Define Classifier
def make_model():
    input = keras.layers.Input(shape=(28, 28, 1))
    conv2d_1 = keras.layers.Conv2D(8, (5,5), strides=(3,3),activation='relu')(input)
    conv2d_2 = keras.layers.Conv2D(16, (3,3), strides=(2,2),activation='relu')(conv2d_1)
    flatten = keras.layers.Flatten()(conv2d_2)
    output = keras.layers.Dense(10, activation='softmax')(flatten)
    model = keras.models.Model(input, output)
    model.compile(
        loss = tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
        optimizer = keras.optimizers.Adam(learning_rate=1e-3),
        metrics = 'acc'
    )
    return model
keras.backend.clear_session()
model = make_model()
model.summary()

#%% [markdown]
# ### Training model
model.fit(x_train, y_train, batch_size=128, epochs=20)

#%% [markdown]
# ### Evaluate model
model.evaluate(x_test, y_test)

#%% [markdown]
# ### Save model
model.save('digit_classifier_CNN.h5')