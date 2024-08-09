#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>

#include <esp_err.h>
#include <esp_log.h>
#include <esp_littlefs.h>

#include "arena.h"

char *FS_TAG = "FILESYSTEM";

enum FS_CODES
{
    FS_OK,
    FS_ERROR_INITIALIZE,
    FS_ERROR_MOUNT,
    FS_ERROR_PARTITION,
    FS_ERROR_MISSING_PARTITION
};

esp_vfs_littlefs_conf_t fs_conf = 
{
    .base_path = "/fs",
    .partition_label = "fs",
    .format_if_mount_failed = true,
    .dont_mount = false
};

typedef struct
{
    uint8_t *section1;
    uint8_t *section2;
    uint8_t *section3;
    uint8_t *section4;
    size_t size;   
} dlms_mem_arena;

int littlefs_init()
{
    esp_err_t ret = esp_vfs_littlefs_register(&fs_conf);

    switch (ret)
    {
        case ESP_OK:
        break;
    
        case ESP_FAIL:
        return FS_ERROR_MOUNT;

        case ESP_ERR_NOT_FOUND:
        return FS_ERROR_MISSING_PARTITION; 

        default:
        return FS_ERROR_INITIALIZE;
    }

    size_t total = 0, used = 0;
    ret = esp_littlefs_info(fs_conf.partition_label, &total, &used);

    if(ret != ESP_OK && used > total)
    {
        return FS_ERROR_PARTITION;
    }

    return FS_OK;
}

void app_main(void)
{

    printf("Initializing littlefs. code: %i\n", littlefs_init());

    size_t size = (512 * 5) + (1024 * 5) + (66 * 5);
    void *buffer = malloc(size);
    if(buffer == NULL)
    {
        return;
    }
    arena a = arena_init(buffer, size);
    allocator arloc = arena_alloc_init(&a);

    dlms_mem_arena dlms_ar;

    dlms_ar.size = a.size;

    dlms_ar.section1 = make(uint8_t, 512, arloc);
    dlms_ar.section2 = make(uint8_t, 512, arloc);
    dlms_ar.section3 = make(uint8_t, 512, arloc);
    dlms_ar.section4 = make(uint8_t, 512, arloc);
    int *x = make(int, 1, arloc);

    for(int i = 0; i < 512; i += 1) dlms_ar.section1[i] = 'a';
    for(int i = 0; i < 512; i += 1) dlms_ar.section2[i] = 'b';
    for(int i = 0; i < 512; i += 1) dlms_ar.section3[i] = 'c';
    for(int i = 0; i < 512; i += 1) dlms_ar.section4[i] = 'd';

    for(int i = 0; i < 512; i += 1) printf("%c\n", dlms_ar.section1[i]);
    for(int i = 0; i < 512; i += 1) printf("%c\n", dlms_ar.section2[i]);
    for(int i = 0; i < 512; i += 1) printf("%c\n", dlms_ar.section3[i]);
    for(int i = 0; i < 512; i += 1) printf("%c\n", dlms_ar.section4[i]);
   
}