#include "wb_watchdog.h"
#include "esp_task_wdt.h"
#include "esp_idf_version.h"

static uint32_t _origTimeoutS = 5;

namespace wb_wdt {

void capture() {
    _origTimeoutS = 5;
}

void extendTo(uint32_t seconds) {
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    esp_task_wdt_config_t cfg;
    cfg.timeout_ms    = seconds * 1000;
    cfg.idle_core_mask = 0;
    cfg.trigger_panic  = false;
    esp_task_wdt_reconfigure(&cfg);
#else
    esp_task_wdt_init(seconds, false);
#endif
}

void restore() {
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    esp_task_wdt_config_t cfg;
    cfg.timeout_ms    = _origTimeoutS * 1000;
    cfg.idle_core_mask = 0;
    cfg.trigger_panic  = false;
    esp_task_wdt_reconfigure(&cfg);
#else
    esp_task_wdt_init(_origTimeoutS, false);
#endif
}

} // namespace wb_wdt