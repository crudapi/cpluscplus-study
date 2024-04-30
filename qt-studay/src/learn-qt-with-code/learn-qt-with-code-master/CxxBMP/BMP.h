#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;

#pragma pack(1)
struct BMPInfoHeader
{
	friend ostream& operator<<(ostream& os, const BMPInfoHeader& header);

	uint32_t size{0};		 // Size of this header (in bytes)
	int32_t width{0};		 // width of bitmap in pixels
	int32_t height{0};		 // width of bitmap in pixels
							 //       (if positive, bottom-up, with origin in lower left corner)
							 //       (if negative, top-down, with origin in upper left corner)
	uint16_t planes{1};		 // No. of planes for the target device, this is always 1
	uint16_t bit_count{0};	 // No. of bits per pixel
	uint32_t compression{0}; // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
	uint32_t size_image{0};	 // 0 - for uncompressed images
	int32_t x_pixels_per_meter{0};
	int32_t y_pixels_per_meter{0};
	uint32_t colors_used{0};	  // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
	uint32_t colors_important{0}; // No. of colors used for displaying the bitmap. If 0 all colors are required
};

struct  BMPColorHeader
{
	friend ostream& operator<<(ostream& os, const BMPColorHeader& header);

	uint32_t red_mask{0x00ff0000};		   // Bit mask for the red channel
	uint32_t green_mask{0x0000ff00};	   // Bit mask for the green channel
	uint32_t blue_mask{0x000000ff};		   // Bit mask for the blue channel
	uint32_t alpha_mask{0xff000000};	   // Bit mask for the alpha channel
	uint32_t color_space_type{0x73524742}; // Default "sRGB" (0x73524742)
	uint32_t unused[16]{0};				   // Unused data for sRGB color space
};

struct  BMPFileHeader
{
	friend ostream& operator<<(ostream& os, const BMPFileHeader& header);
	
	uint16_t file_type{0x4D42}; // File type always BM which is 0x4D42
	uint32_t file_size{0};		// Size of the file (in bytes)
	uint16_t reserved1{0};		// Reserved, always 0
	uint16_t reserved2{0};		// Reserved, always 0
	uint32_t offset_data{0};	// Start position of pixel data (bytes from the beginning of the file)
};
#pragma pack()

struct  BMP
{
	BMP(const string& fname);
	BMP(int32_t width, int32_t height, bool has_alpha = false);
	BMP(int w, int h, unsigned char r, unsigned char g, unsigned char b);

	//用来在内存中自己构造RGB数据填充到BMP对象内部;同时也据此生成BGR数据，从而可以输出到文件
	void set_rgb_data(const unsigned char* data_buffer, int data_length);
	void read(const string& fname);
	void save_to(const string& fname);
	void fill_region(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h
		, uint8_t B, uint8_t G, uint8_t R, uint8_t A);
	void fill_region(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h
		, uint8_t B, uint8_t G, uint8_t R);
	const std::vector<uint8_t>& get_rgb_buffer(void) const;
	int get_width(void) const { return m_bmp_info_header.width; }
	int get_height(void) const { return m_bmp_info_header.height; }
	// ...
	BMPFileHeader m_file_header;
	BMPInfoHeader m_bmp_info_header;
	BMPColorHeader bmp_color_header;
	vector<uint8_t> m_bgr_from_file;//RGBA RAW数据,直接从BMP文件里读取到的；如果自己在内存构造BMP对象，也是先用空数据填充这个数组
	vector<uint8_t> m_rgb;//给内存使用的RGB数据
private:
	// ...

	// Check if the pixel data is stored as BGRA and if the color space type is sRGB
	void check_color_header(BMPColorHeader &bmp_color_header);
	//rgb => bgr ; bgr => rgb
	static void bgr_and_rgb_convert(const char in[],
		const int image_width,
		const int image_height,
		char out[]);
private:
	uint32_t m_row_stride{0};//宽度*3个（也可能是4个）分量，是一行的字节数

	void write_headers(std::ofstream &of);

	void write_headers_and_data(std::ofstream &of);

	// Add 1 to the m_row_stride until it is divisible with align_stride
	uint32_t make_stride_aligned(uint32_t align_stride);
};
