#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.c"
#include "stb_image_write.c"

void mergeImagesWithAlpha(
        uint8_t* image1, uint8_t* image2,
        int width, int height, int channels, float alpha,
        uint8_t* mergedImage
) {
    for (int i = 0; i < width * height * channels; ++i) {
        mergedImage[i] = static_cast<uint8_t>(
                (1.0f - alpha) * image1[i] + alpha * image2[i]
        );
    }
}