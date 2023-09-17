#include "QrToPng.h"
#include "AddBack.h"

int main() {

    std::string qrText = "https://www.tsinghua.edu.cn/";
    std::string fileName = "normal.png";

    int imgSize = 300;
    int minModulePixelSize = 3;
    auto exampleQrPng1 = QrToPng(fileName, imgSize, minModulePixelSize, qrText, true, qrcodegen::QrCode::Ecc::MEDIUM);

    std::cout << "Writing Example QR code 1 (normal) to " << fileName << " with text: '" << qrText << "', size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng1.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;

    fileName = "tiny.png";
    imgSize = 40;
    minModulePixelSize = 1;
    auto exampleQrPng2 = QrToPng(fileName, imgSize, minModulePixelSize, qrText, true, qrcodegen::QrCode::Ecc::LOW);
    std::cout << "Writing Example QR code 2 (tiny) to " << fileName << " with text: '" << qrText << "', size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng2.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;


    fileName = "Huge.png";
    imgSize = 1080;
    minModulePixelSize = 20;
    auto exampleQrPng3 = QrToPng(fileName, imgSize, minModulePixelSize, qrText, true, qrcodegen::QrCode::Ecc::HIGH);
    std::cout << "Writing Example QR code 3 (huge) to " << fileName << " with text: '" << qrText << "', size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng3.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;


    qrText = "清华是个好学校:)";

    fileName = "Text.png";
    imgSize = 1024;
    minModulePixelSize = 1;
    auto exampleQrPng4 = QrToPng(fileName, imgSize, minModulePixelSize,
                                 qrText, true, qrcodegen::QrCode::Ecc::HIGH);
    std::cout << "Writing Example QR code 4 (Text) to " << fileName << " with qrText, size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng4.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;

    // The following is adding background.
    // Load the first image
    int image1_width, image1_height, image1_channels;
    unsigned char* image1_data = stbi_load("Back.png", &image1_width, &image1_height, &image1_channels, 0);
    if (!image1_data) {
        std::cerr << "Failed to load image1." << std::endl;
        return 1;
    }

    // Load the second image
    int image2_width, image2_height, image2_channels;
    unsigned char* image2_data = stbi_load("Text.png", &image2_width, &image2_height, &image2_channels, 0);
    if (!image2_data) {
        std::cerr << "Failed to load image2." << std::endl;
        stbi_image_free(image1_data);
        return 1;
    }

    // Convert channels from 3 to 4
    if(image2_channels==3){
        // Create a new buffer for the 4-channel RGBA image
        std::vector<unsigned char> rgba_data(image2_width * image2_height * 4);

        // Convert RGB to RGBA by adding an opaque alpha channel
        for (int i = 0, j = 0; i < image2_width * image2_height * 3; i += 3, j += 4) {
            rgba_data[j] = image2_data[i];       // Red channel
            rgba_data[j + 1] = image2_data[i + 1]; // Green channel
            rgba_data[j + 2] = image2_data[i + 2]; // Blue channel
            rgba_data[j + 3] = 255;             // Alpha channel (fully opaque)
        }

        // Save the result as a 4-channel RGBA image
        stbi_write_png("NewText.png", image2_width, image2_height, 4, rgba_data.data(), 0);

        // Free the original image data
        stbi_image_free(image2_data);

        std::cout << "Conversion image \"Text\" from RGB to RGBA completed. Result saved as image_rgba.png." << std::endl;
        image2_data = stbi_load("NewText.png", &image2_width, &image2_height, &image2_channels, 0);
    }


    // Check if the images have the same dimensions
    if (image1_width != image2_width || image1_height != image2_height || image1_channels != image2_channels) {
        std::cerr << "Images must have the same dimensions and channels." << std::endl;
        stbi_image_free(image1_data);
        stbi_image_free(image2_data);
        return 1;
    }

    // Create a new image for the result
    int result_width = image1_width;
    int result_height = image1_height;
    int result_channels = image1_channels;
    std::vector<unsigned char> result_data(result_width * result_height * result_channels);

    // Alpha value for blending
    float alpha = 0.4f;

    // Perform pixel-wise blending
    for (int i = 0; i < result_width * result_height * result_channels; ++i) {
        result_data[i] = static_cast<unsigned char>((1 - alpha) * image1_data[i] + alpha * image2_data[i]);
    }

    // Save the result image
    stbi_write_png("Merge.png", result_width, result_height, result_channels, result_data.data(), 0);

    // Free the image data
    stbi_image_free(image1_data);
    stbi_image_free(image2_data);

    std::cout << "Image blending complete. Result saved as result.png." << std::endl;
    return 0;
}