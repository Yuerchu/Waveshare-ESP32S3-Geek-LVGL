/**
 * ESP32-S3 LVGL 9.4.0 演示程序
 * 集成按钮检测和LVGL图形界面
 */

#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include <OneButton.h>

// 屏幕分辨率配置
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 135

// LCD引脚定义（根据README配置）
#define TFT_MOSI 11  // 数据
#define TFT_SCLK 12  // 时钟
#define TFT_DC 8     // 数据/命令
#define TFT_RST 9    // 复位
#define TFT_CS 10    // 片选
#define TFT_BL 7     // 背光

// 按钮引脚
#define PIN_INPUT 0

// LVGL缓冲区大小
#define LVGL_BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10)

// 全局对象
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED /* MISO */);
Arduino_GFX *gfx = new Arduino_ST7789(bus, TFT_RST, 1 /* rotation */, true /* IPS */, SCREEN_HEIGHT, SCREEN_WIDTH, 53 /* col_offset1 */, 40 /* row_offset1 */, 53 /* col_offset2 */, 40 /* row_offset2 */);

OneButton button(PIN_INPUT, true);

// LVGL显示缓冲区
static lv_color_t buf1[LVGL_BUFFER_SIZE];
static lv_color_t buf2[LVGL_BUFFER_SIZE];

// LVGL UI对象
lv_obj_t *label_status;
lv_obj_t *label_info;
lv_obj_t *btn_test;
lv_obj_t *bar_progress;

// LVGL显示刷新回调
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);

  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
  lv_disp_flush_ready(disp);
}

// 创建LVGL界面
void create_ui() {
  lv_obj_t *screen = lv_screen_active();
  lv_obj_set_style_bg_color(screen, lv_color_hex(0x1a1a1a), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
  

  label_status = lv_label_create(screen);
  lv_label_set_text(label_status, "状态: 正常");
  lv_obj_align(label_status, LV_ALIGN_TOP_MID, 0, 10);


  label_info = lv_label_create(screen);
  lv_label_set_text(label_info, "信息: 无");
  lv_obj_align(label_info, LV_ALIGN_TOP_MID, 0, 30);


  btn_test = lv_btn_create(screen);
  lv_obj_set_size(btn_test, 100, 50);
  lv_obj_align(btn_test, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(btn_test, btn_test_event_handler, LV_EVENT_ALL, NULL);
  
  lv_obj_invalidate(screen);
}

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32-S3 LVGL 9.4.0 Demo Starting...");

  // 初始化LCD
  gfx->begin();
  gfx->fillScreen(BLACK);

  // 设置背光
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // 初始化LVGL
  lv_init();

  // 创建显示设备
  lv_display_t *disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_display_set_flush_cb(disp, my_disp_flush);
  lv_display_set_buffers(disp, buf1, buf2, LVGL_BUFFER_SIZE * sizeof(lv_color_t), LV_DISPLAY_RENDER_MODE_PARTIAL);

  // 创建UI界面
  create_ui();

  // 初始化按钮
  button.attachLongPressStart(LongPressStart, &button);
  button.attachClick(Click, &button);
  button.attachDoubleClick(DoubleClick, &button);
  button.setLongPressIntervalMs(1000);

  Serial.println("Initialization complete!");
  Serial.println("Press the button to test!");
}

void loop() {
  // 更新LVGL任务
  lv_timer_handler();

  // 检测按钮状态
  button.tick();

  delay(5);
}

// this function will be called when the button started long pressed.
void LongPressStart(void *oneButton)
{
  lv_label_set_text(label_info, "Long Press");
}

void Click(void *oneButton)
{
  lv_label_set_text(label_info, "Click Detected");
}

void DoubleClick(void *oneButton)
{
  lv_label_set_text(label_info, "Double Click Detected");
}