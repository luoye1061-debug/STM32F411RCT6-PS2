# STM32F411RCT6-PS2-CAR

基于 STM32F411RCT6 微控制器与 HAL 库开发的 PS2 手柄通信例程

---

## 📂 目录结构与模块说明

### 1. `01_PS2_UART_Demo`
* **定位**：STM32F411RCT6 与 PS2 无线手柄的独立通信与键值解析例程。
* **实现底层**：基于 GPIO 模拟高频 SPI 时序（软件 SPI）实现手柄数据读取，并通过 UART 串口打印解析后的键值，便于前期调试。

---

## 🛠️ 技术栈
* **MCU**: STM32F411RCT6
* **SDK**: STM32Cube 固件库 (HAL 库)
* **外设与驱动**: 软件 SPI (GPIO 模拟),  UART
