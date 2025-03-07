from PIL import Image
import numpy as np

def rgb888_to_rgb565(r, g, b):
    """Convert 8-bit R, G, B values to a single 16-bit RGB565 value."""
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

def image_to_rgb565(image_path):
    """Convert an image to a uint8_t RGB565 array."""
    # Load and convert image to RGB format
    img = Image.open(image_path).convert('RGB')
    
    width, height = img.size
    pixel_data = np.array(img)

    # Create a uint8_t array (2 bytes per pixel)
    uint8_array = []

    for y in range(height):
        for x in range(width):
            r, g, b = pixel_data[y, x]
            rgb565 = rgb888_to_rgb565(r, g, b)
            uint8_array.append(rgb565 & 0xFF)        # Low byte
            uint8_array.append((rgb565 >> 8) & 0xFF) # High byte

    return uint8_array, width, height

def save_array_as_c_file(array, width, height, output_file="image_rgb565.c"):
    """Save the uint8_t RGB565 array to a C header file."""
    with open(output_file, "w") as f:
        f.write(f"// RGB565 Image: {width}x{height}\n")
        f.write(f"#define IMAGE_WIDTH {width}\n")
        f.write(f"#define IMAGE_HEIGHT {height}\n\n")
        f.write("const uint8_t image_data[] = {\n    ")

        hex_values = [f"0x{byte:02X}" for byte in array]
        for i, value in enumerate(hex_values):
            f.write(value + (", " if (i + 1) % 16 else ",\n    "))

        f.write("\n};\n")

# Example Usage
image_path = "image.jpg"  # Change to your image path
rgb565_array, width, height = image_to_rgb565(image_path)

# Save as C file
save_array_as_c_file(rgb565_array, width, height)

print(f"Image converted: {width}x{height} -> {len(rgb565_array)} uint8_t elements")
