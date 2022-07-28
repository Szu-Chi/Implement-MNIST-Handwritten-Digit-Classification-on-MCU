# **Implement MNIST Handwritten Digit Classification on MCU**
This repository demonstrate how to implement CNN on MCU by using STM32 X-Cube-AI.
| Environment | <!-- -->             |
|-------------|----------------------|
| OS          | Win11                |
| MCU         | NUCLEO-F411RE        |
| Python      | 3.9.12               |
| Keras       | 2.6.0                |
| Tensorflow  | 2.8.0                |
| X-Cube-AI   | 7.2.0                |
| IDE         | VScode, STM32CubeIDE |

Workflow:
1. Using Keras build classification model.
2. Create STM32 project.
3. Testing classification performance on MCU

# Using Keras build classification model.
```
python3 train_model.py
```
![image](img/convnet.png)
---
Model Summary
---
|Layer (type)           |      Output Shape         |     Param #   |
|-----------------------|---------------------------|---------------|
|input_1 (InputLayer)   |      [(None, 28, 28, 1)]  |     0         |
|conv2d (Conv2D)        |      (None, 8, 8, 8)      |     208       |
|conv2d_1 (Conv2D)      |      (None, 3, 3, 16)     |     1168      |
|flatten (Flatten)      |      (None, 144)          |     0         |
|dense (Dense)          |      (None, 10)           |     1450      |

Total params: 2,826\
Trainable params: 2,826\
Non-trainable params: 0

# Create STM32 project.
## Step 1 Create New STM32 project:
1. Select NUCLEO-F411RE\
    ![image](img/Select_NUCLEO-F411RE.png)
2. Create STM32 Project\
    ![image](img/create_stm32_project.png)


## Step 2 Setup STM32 Peripherals:
### 1. **X-Cube-AI**
- Click Software Packs -> Select Components
    ![image](img/Select%20Components.png)
- Enable X-CUBE-AI Core
    ![image](img/Enable%20X-CUBE-AI%20Core.png)
- Add Network
    - Software Packs -> STMicroelectronics.X-CUBE-AI.7.2.0 -> Add network
    - Change model name to digit_cnn
    - Click Browse button select pre-trained model digit_classifier_CNN.h5
    - Software Packs -> STMicroelectronics.X-CUBE-AI.7.2.0 -> Analyze
    ![image](img/add%20network%20%26%20analyze.png)
- Software Packs -> STMicroelectronics.X-CUBE-AI.7.2.0 -> Show graph\    
    ![image](img/Show%20graph.png)

### 2. **Activate TIM11**
![image](img/activate%20TIM11.png)

### 3. **Enable Virtual Com Port Global Interrupt**
![image](img/Enable%20VCP%20Global%20Interrupt.png)

### 4. **Enable generate peripheral initalization as a pair of '.c/.h' file per peripheral**
![image](img/Enable%20generate%20peripheral%20initalization%20as%20a%20pair%20of%20%20file%20per%20peripheral.png)

### 5. **Generate code and Replace Scirpt**
- Core/Inc/main.h
- Core/Src/main.c
- Core/Src/stm32f4xx_it.c

### 6. **Upload program to STM32**


# Testing classification performance on MCU
This repository testing architecture shown as below figure.
![image](img/Testing%20Architecture.png)
```
python3 testing_on_mcu.py
```
# Demo Video Link:
* [Using Keras build classification model]
* [Create STM32 project]
* [Testing classification performance on MCU]

# Reference:
* [TensorFlow 2 quickstart for beginners](https://www.tensorflow.org/tutorials/quickstart/beginner)
* [TensorFlow 2 quickstart for experts](https://www.tensorflow.org/tutorials/quickstart/advanced)
* [TinyML: Gettting Started with STM32 X-CUBE-AI](https://www.digikey.tw/en/maker/projects/tinyml-getting-started-with-stm32-x-cube-ai/f94e1c8bfc1e4b6291d0f672d780d2c0)
* X-CUBE-AI Expansion Package Embedded Documentation
