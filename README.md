# Wio LTE for Mbed

Wio LTE for Mbed�́AWio LTE��Mbed�œ��������߂̃v���O�����ƃ��C�u�����ł��B

�{���|�W�g���́A�iSeeedJP�ɒu���Ă���܂����j**Seeed�̔�������|�W�g��**�ł��B�����ӂ��������B

> Seeed��Wio LTE�̌�p���i��Arm Mbed�𐳎��ɃT�|�[�g����\��ł��B

# �ł��邱�ƁE�ł��Ȃ�����

* �Z Mbed CLI���g�����}�C�R���̊J��
* �Z LTE���W���[���̓d��ON�A������
* �� LTE���W���[���ւ�AT�R�}���h���s
* �~ NetworkInterface�N���X

# �J�����̍\�z�菇

## Arm Mbed CLI���C���X�g�[��

[Arm Mbed CLI�̊��\�z for Windows](https://qiita.com/matsujirushi/items/bf4db4514a753f794643)���Q�l�ɁAMbed CLI�̊J�������Z�b�g�A�b�v���Ă��������B

## Wio LTE for Mbed���C���|�[�g

github����Mbed CLI�R�}���h��Wio LTE for Mbed���C���|�[�g���Ă��������B

> �����_��Wio LTE for Mbed�́A���C�u�������������ꂽ�v���O�����ł��B���������āA**mbed-cli add**�ł͂Ȃ��A**mbed-cli import**�Ŏ擾���܂��B

```
C:\mbed>mbed-cli import https://github.com/SeeedJP/WioLTEforMbed
[mbed] Importing program "WioLTEforMbed" from "https://github.com/SeeedJP/WioLTEforMbed" at latest revision in the current branch
[mbed] Adding library "BufferedSerial" from "https://os.mbed.com/users/sam_grove/code/BufferedSerial" at rev #a0d37088b405
[mbed] Adding library "BufferedSerial\Buffer" from "https://mbed.org/users/sam_grove/code/Buffer" at rev #89564915f2a7
[mbed] Adding library "mbed-dev" from "https://os.mbed.com/users/mbed_official/code/mbed-dev" at rev #b0033dcd6934
[mbed] Couldn't find build tools in your program. Downloading the mbed 2.0 SDK tools...

C:\mbed>
```

## targets.json ��ύX

**mbed-dev\targets\targets.json**�t�@�C����**MTS_MDOT_F405RG**��**HSE_VALUE**���A**26000000**����**8000000**�ɕύX���Ă��������B

> Wio LTE��Mbed�̐����ȑΉ��{�[�h�ł͂Ȃ��̂ŁATARGET��WioLTE���w�肵�ăR���p�C�����邱�Ƃ��ł��܂���B
> �ł��ގ����Ă���MTS_MDOT_F405RG�{�[�h�̐ݒ��ύX���đΉ����܂��B

### �ύX�O
```json
    "MTS_MDOT_F405RG": {
        "inherits": ["FAMILY_STM32"],
        "core": "Cortex-M4F",
        "extra_labels_add": ["STM32F4", "STM32F405RG"],
        "is_disk_virtual": true,
        "macros_add": ["HSE_VALUE=26000000"],
        "device_has_add": ["ANALOGOUT"],
        "release_versions": ["2"],
        "device_name": "STM32F405RG"
    },
```

### �ύX��
```json
    "MTS_MDOT_F405RG": {
        "inherits": ["FAMILY_STM32"],
        "core": "Cortex-M4F",
        "extra_labels_add": ["STM32F4", "STM32F405RG"],
        "is_disk_virtual": true,
        "macros_add": ["HSE_VALUE=8000000"],
        "device_has_add": ["ANALOGOUT"],
        "release_versions": ["2"],
        "device_name": "STM32F405RG"
    },
```

## PeripheralNames.h ��ύX

**mbed-dev\targets\TARGET_STM\TARGET_STM32F4\TARGET_MTS_MDOT_F405RG\PeripheralNames.h**�t�@�C����**STDIO_UART_xxx**��3�s���A���L�̂Ƃ���ύX���Ă��������B

### �ύX�O
```cpp
#define STDIO_UART_TX  PA_2
#define STDIO_UART_RX  PA_3
#define STDIO_UART     UART_2
```

### �ύX��
```cpp
#define STDIO_UART_TX  PB_6
#define STDIO_UART_RX  PB_7
#define STDIO_UART     UART_1
```

## �R���p�C��

�R���p�C��������Ɋ������邩�m�F���Ă��������B

```
C:\mbed\WioLTEforMbed>mbed compile -m MTS_MDOT_F405RG -t GCC_ARM
Building project WioLTEforMbed (MTS_MDOT_F405RG, GCC_ARM)
Scan: .
Scan: env
Scan: mbed
Compile [  0.6%]: MyBuffer.cpp
...
Image: .\BUILD\MTS_MDOT_F405RG\GCC_ARM\WioLTEforMbed.bin

C:\mbed\WioLTEforMbed>
```
