# Wio LTE for Mbed

Wio LTE for Mbedは、Wio LTEをMbedで動かすためのプログラムとライブラリです。

本リポジトリは、（SeeedJPに置いてありますが）**Seeedの非公式リポジトリ**です。ご注意ください。

> SeeedはWio LTEの後継製品でArm Mbedを正式にサポートする予定です。

# できること・できないこと

* 〇 Mbed CLIを使ったマイコンの開発
* 〇 LTEモジュールの電源ON、初期化
* △ LTEモジュールへのATコマンド発行
* × NetworkInterfaceクラス

# 開発環境の構築手順

## Arm Mbed CLIをインストール

[Arm Mbed CLIの環境構築 for Windows](https://qiita.com/matsujirushi/items/bf4db4514a753f794643)を参考に、Mbed CLIの開発環境をセットアップしてください。

## Wio LTE for Mbedをインポート

githubからMbed CLIコマンドでWio LTE for Mbedをインポートしてください。

> 現時点のWio LTE for Mbedは、ライブラリが同封されたプログラムです。したがって、**mbed-cli add**ではなく、**mbed-cli import**で取得します。

```
C:\mbed>mbed-cli import https://github.com/SeeedJP/WioLTEforMbed
[mbed] Importing program "WioLTEforMbed" from "https://github.com/SeeedJP/WioLTEforMbed" at latest revision in the current branch
[mbed] Adding library "BufferedSerial" from "https://os.mbed.com/users/sam_grove/code/BufferedSerial" at rev #a0d37088b405
[mbed] Adding library "BufferedSerial\Buffer" from "https://mbed.org/users/sam_grove/code/Buffer" at rev #89564915f2a7
[mbed] Adding library "mbed-dev" from "https://os.mbed.com/users/mbed_official/code/mbed-dev" at rev #b0033dcd6934
[mbed] Couldn't find build tools in your program. Downloading the mbed 2.0 SDK tools...

C:\mbed>
```

## targets.json を変更

**mbed-dev\targets\targets.json**ファイルの**MTS_MDOT_F405RG**の**HSE_VALUE**を、**26000000**から**8000000**に変更してください。

> Wio LTEはMbedの正式な対応ボードではないので、TARGETにWioLTEを指定してコンパイルすることができません。
> 最も類似しているMTS_MDOT_F405RGボードの設定を変更して対応します。

### 変更前
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

### 変更後
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

## PeripheralNames.h を変更

**mbed-dev\targets\TARGET_STM\TARGET_STM32F4\TARGET_MTS_MDOT_F405RG\PeripheralNames.h**ファイルの**STDIO_UART_xxx**の3行を、下記のとおり変更してください。

### 変更前
```cpp
#define STDIO_UART_TX  PA_2
#define STDIO_UART_RX  PA_3
#define STDIO_UART     UART_2
```

### 変更後
```cpp
#define STDIO_UART_TX  PB_6
#define STDIO_UART_RX  PB_7
#define STDIO_UART     UART_1
```

## コンパイル

コンパイルが正常に完了するか確認してください。

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
