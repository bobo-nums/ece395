EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "STM32 External Memory"
Date "2021-08-31"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F4:STM32F407VGTx U?
U 1 1 614FFDC2
P 2650 3800
F 0 "U?" H 2650 911 50  0000 C CNN
F 1 "STM32F407VGTx" H 2650 820 50  0000 C CNN
F 2 "Package_QFP:LQFP-100_14x14mm_P0.5mm" H 1950 1200 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00037051.pdf" H 2650 3800 50  0001 C CNN
	1    2650 3800
	1    0    0    -1  
$EndComp
$Comp
L micro_sd_card_adafruit:Micro_SD_Card_Adafruit J?
U 1 1 61515836
P 6100 2450
F 0 "J?" H 5700 3200 50  0000 L CNN
F 1 "Micro_SD_Card_Adafruit" H 5950 3200 50  0000 L CNN
F 2 "" H 8150 3150 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 6100 2550 50  0001 C CNN
	1    6100 2450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
