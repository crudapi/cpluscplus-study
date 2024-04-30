#include "BMP.h"
#include <cassert>

ostream & operator<<(ostream & os, const BMPInfoHeader & header)
{
	os
		<< "head size=" << header.size
		<< ", width=" << header.width
		<< ", height=" << header.height
		<< ", bit_count=" << header.bit_count
		//<< ", compression=" << header.compression
		//<< ", size_image=" << header.size_image
		//<< ", x_pixels_per_meter=" << header.x_pixels_per_meter
		//<< ", y_pixels_per_meter=" << header.y_pixels_per_meter
		//<< ", colors_used=" << header.colors_used
		//<< ", colors_important=" << header.colors_important
		;

	return os;
}

ostream & operator<<(ostream & os, const BMPColorHeader & header)
{
	//uint32_t red_mask{ 0x00ff0000 };		   // Bit mask for the red channel
	//uint32_t green_mask{ 0x0000ff00 };	   // Bit mask for the green channel
	//uint32_t blue_mask{ 0x000000ff };		   // Bit mask for the blue channel
	//uint32_t alpha_mask{ 0xff000000 };	   // Bit mask for the alpha channel
	//uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
	//uint32_t unused[16]{ 0 };				   // Unused data for sRGB color space
	os
		<< "red_mask=" << std::hex << header.red_mask
		<< ", green_mask=" << header.green_mask
		<< ", blue_mask=" << header.blue_mask
		<< ", alpha_mask=" << header.alpha_mask
		<< ", color_space_type=" << header.color_space_type
		<< ", unused[0]=" << header.unused[0]
		;

	return os;
}

ostream & operator<<(ostream & os, const BMPFileHeader & header)
{
	os 
		<< "file_type=" << std::hex << header.file_type 
		<< dec
		<< ", file_size=" << header.file_size
		<< ", offset_data=" << header.offset_data
		;

	return os;
}

BMP::BMP(const string& fname)
{
	read(fname);
	m_rgb.resize(m_bgr_from_file.size());
	bgr_and_rgb_convert((const char*)m_bgr_from_file.data(), m_bmp_info_header.width, m_bmp_info_header.height
		, (char*)m_rgb.data());
}

BMP::BMP(int32_t width, int32_t height, bool has_alpha)
{
	if (width <= 0 || height <= 0)
	{
		throw std::runtime_error("The image width and height must be positive numbers.");
	}

	m_bmp_info_header.width = width;
	m_bmp_info_header.height = height;
	if (has_alpha)
	{
		m_bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
		m_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);

		m_bmp_info_header.bit_count = 32;
		m_bmp_info_header.compression = 3;
		m_row_stride = width * 4;
		m_bgr_from_file.resize(m_row_stride * height);
		m_file_header.file_size = m_file_header.offset_data + static_cast<uint32_t>(m_bgr_from_file.size());
	}
	else
	{
		m_bmp_info_header.size = sizeof(BMPInfoHeader);
		m_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

		m_bmp_info_header.bit_count = 24;
		m_bmp_info_header.compression = 0;
		m_row_stride = width * 3;//宽度*3个分量，是一行的字节数
		m_bgr_from_file.resize(m_row_stride * height);

		uint32_t new_stride = make_stride_aligned(4);
		m_file_header.file_size = m_file_header.offset_data + static_cast<uint32_t>(m_bgr_from_file.size())
			+ m_bmp_info_header.height * (new_stride - m_row_stride);
	}
}

BMP::BMP(int w, int h, unsigned char r, unsigned char g, unsigned char b) :BMP(w, h)
{
	vector<unsigned char> arr(w * h * 3);

	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			int pixIndex = (row * w + col) * 3;
			arr[pixIndex + 0] = r;
			arr[pixIndex + 1] = g;
			arr[pixIndex + 2] = b;
		}
	}
	set_rgb_data(arr.data(), arr.size());
}

void BMP::set_rgb_data(const unsigned char* data_buffer, int data_length)
{
	int w = m_bmp_info_header.width;
	int h = m_bmp_info_header.height;
	assert(w * h * m_bmp_info_header.bit_count / 8 == data_length);
	m_rgb.assign(data_buffer, data_buffer + data_length);
	bgr_and_rgb_convert((const char*)m_rgb.data(), w, h, (char*)m_bgr_from_file.data());
}

void BMP::read(const string& fname)
{
	std::ifstream inbmpfile{ fname, std::ios_base::binary };
	if (inbmpfile)
	{
		//cout << "read file " << fname << endl;

		auto size_of_header = sizeof(m_file_header);
		//std::cout << "size of file_header=" << size_of_header << std::endl;
		inbmpfile.read((char *)&m_file_header, size_of_header);
		if (m_file_header.file_type != 0x4D42)
		{
			throw std::runtime_error("Error! Unrecognized file format.");
		}
		//cout << "file head: " << m_file_header << endl;

		auto size_of_bmp_info_header = sizeof(m_bmp_info_header);
		//std::cout << "size_of_bmp_info_header=" << size_of_bmp_info_header << std::endl;
		inbmpfile.read((char *)&m_bmp_info_header, sizeof(m_bmp_info_header));
		//cout << "bmp info header: " << m_bmp_info_header << endl;

		// The BMPColorHeader is used only for transparent images
		if (m_bmp_info_header.bit_count == 32)
		{
			// Check if the file has bit mask color information
			if (m_bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader)))
			{
				inbmpfile.read((char *)&bmp_color_header, sizeof(bmp_color_header));
				// Check if the pixel data is stored as BGRA and if the color space type is sRGB
				check_color_header(bmp_color_header);
			}
			else
			{
				std::cout << "Warning ! the file " << fname << " does not seem to contain bit mask infor" << std::endl;
				throw std::runtime_error("Error! Unrecognized file format.");
			}
		}

		// Jump to the pixel data location
		inbmpfile.seekg(m_file_header.offset_data, inbmpfile.beg);

		// Adjust the header fields for output.
		// Some editors will put extra info in the image file, we only save the headers and the data.
		if (m_bmp_info_header.bit_count == 32)
		{
			m_bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
			m_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
		}
		else
		{
			m_bmp_info_header.size = sizeof(BMPInfoHeader);
			m_file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
		}
		//std::cout << "offset_data=" << m_file_header.offset_data << std::endl;

		m_file_header.file_size = m_file_header.offset_data;

		if (m_bmp_info_header.height < 0)
		{
			throw std::runtime_error("The m_program can treat only BMP images with the origin in the bottom left corner!");
		}

		m_bgr_from_file.resize(m_bmp_info_header.width * m_bmp_info_header.height * m_bmp_info_header.bit_count / 8);

		// Here we check if we need to take into account row padding
		if (m_bmp_info_header.width % 4 == 0)
		{
			inbmpfile.read((char *)m_bgr_from_file.data(), m_bgr_from_file.size());
			m_file_header.file_size += static_cast<uint32_t>(m_bgr_from_file.size());
		}
		else
		{
			m_row_stride = m_bmp_info_header.width * m_bmp_info_header.bit_count / 8;
			uint32_t new_stride = make_stride_aligned(4);
			std::vector<uint8_t> padding_row(new_stride - m_row_stride);

			for (int y = 0; y < m_bmp_info_header.height; ++y)
			{
				inbmpfile.read((char *)(m_bgr_from_file.data() + m_row_stride * y), m_row_stride);
				inbmpfile.read((char *)padding_row.data(), padding_row.size());
			}
			m_file_header.file_size += static_cast<uint32_t>(m_bgr_from_file.size()) 
				+ m_bmp_info_header.height * static_cast<uint32_t>(padding_row.size());
		}
		//std::cout << "file " << fname << " size=" << m_file_header.file_size << std::endl;
	}
	else
	{
		throw std::runtime_error("Unable to open the input image file:"+fname);
	}
}

void BMP::save_to(const string& fname)
{
	std::ofstream of{ fname, std::ios_base::binary };
	if (of)
	{
		if (m_bmp_info_header.bit_count == 32)
		{
			write_headers_and_data(of);
		}
		else if (m_bmp_info_header.bit_count == 24)
		{
			if (m_bmp_info_header.width % 4 == 0)
			{
				write_headers_and_data(of);
			}
			else
			{
				uint32_t new_stride = make_stride_aligned(4);
				std::vector<uint8_t> padding_row(new_stride - m_row_stride);

				write_headers(of);

				for (int y = 0; y < m_bmp_info_header.height; ++y)
				{
					of.write((const char *)(m_bgr_from_file.data() + m_row_stride * y), m_row_stride);
					of.write((const char *)padding_row.data(), padding_row.size());
				}
			}
		}
		else
		{
			throw std::runtime_error("The m_program can treat only 24 or 32 bits per pixel BMP files");
		}
	}
	else
	{
		throw std::runtime_error("Unable to open the output image file.");
	}
}

const std::vector<uint8_t>& BMP::get_rgb_buffer(void) const {
	return m_rgb;
}

// Check if the pixel data is stored as BGRA and if the color space type is sRGB

void BMP::check_color_header(BMPColorHeader & bmp_color_header)
{
	BMPColorHeader expected_color_header;
	if (expected_color_header.red_mask != bmp_color_header.red_mask ||
		expected_color_header.blue_mask != bmp_color_header.blue_mask ||
		expected_color_header.green_mask != bmp_color_header.green_mask ||
		expected_color_header.alpha_mask != bmp_color_header.alpha_mask)
	{
		throw std::runtime_error("Unexpected color mask format! The m_program expects the pixel data to be in the BGRA format");
	}
	if (expected_color_header.color_space_type != bmp_color_header.color_space_type)
	{
		throw std::runtime_error("Unexpected color space type! The m_program expects sRGB values");
	}
}

inline void BMP::bgr_and_rgb_convert(const char src[], const int image_width, const int image_height, char out[])
{
	int row, column;
	const char *read_ptr;
	char *write_ptr;

	/*
	in  x-> 2 BGRBGRBGR
	in  x-> 1 BGRBGRBGR
	in  x-> 0 BGRBGRBGR

	out x-> 0 RGBRGBRGB
	out x-> 1 RGBRGBRGB
	out x-> 2 RGBRGBRGB
	*/

	for (row = 0; row < image_height; row++)
	{
		read_ptr = &src[row*image_width * 3];
		write_ptr = &out[(image_height - 1 - row)*image_width * 3];
		//memcpy(J0, I0, image_width*3);

		for (column = 0; column < image_width; column++)
		{
			write_ptr[column * 3 + 2] = read_ptr[column * 3 + 0];	//B
			write_ptr[column * 3 + 1] = read_ptr[column * 3 + 1];	//G
			write_ptr[column * 3 + 0] = read_ptr[column * 3 + 2];	//R
		}
	}
}

void BMP::write_headers(std::ofstream & of)
{
	of.write((const char *)&m_file_header, sizeof(m_file_header));
	of.write((const char *)&m_bmp_info_header, sizeof(m_bmp_info_header));
	if (m_bmp_info_header.bit_count == 32)
	{
		of.write((const char *)&bmp_color_header, sizeof(bmp_color_header));
	}
}

void BMP::write_headers_and_data(std::ofstream & of)
{
	write_headers(of);
	of.write((const char *)m_bgr_from_file.data(), m_bgr_from_file.size());
}

// Add 1 to the one_row_length until it is divisible with align_stride

uint32_t BMP::make_stride_aligned(uint32_t align_stride)
{
	uint32_t new_stride = m_row_stride;
	while (new_stride % align_stride != 0)
	{
		new_stride++;
	}
	return new_stride;
}

void BMP::fill_region(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint8_t B, uint8_t G, uint8_t R, uint8_t A)
{
	if (x0 + w > (uint32_t)m_bmp_info_header.width || y0 + h > (uint32_t)m_bmp_info_header.height)
	{
		throw std::runtime_error("The region does not fit in the image!");
	}
	fill_region(x0, y0, w, h, B, G, R);
	uint32_t channels = m_bmp_info_header.bit_count / 8;
	for (uint32_t y = y0; y < y0 + h; ++y)
	{
		for (uint32_t x = x0; x < x0 + w; ++x)
		{
			if (channels == 4)
			{
				m_bgr_from_file[channels * (y * m_bmp_info_header.width + x) + 3] = A;
			}
		}
	}
}
void BMP::fill_region(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint8_t B, uint8_t G, uint8_t R)
{
	if (x0 + w > (uint32_t)m_bmp_info_header.width || y0 + h > (uint32_t)m_bmp_info_header.height)
	{
		throw std::runtime_error("The region does not fit in the image!");
	}

	uint32_t channels = m_bmp_info_header.bit_count / 8;
	for (uint32_t y = y0; y < y0 + h; ++y)
	{
		for (uint32_t x = x0; x < x0 + w; ++x)
		{
			m_bgr_from_file[channels * (y * m_bmp_info_header.width + x) + 0] = B;
			m_bgr_from_file[channels * (y * m_bmp_info_header.width + x) + 1] = G;
			m_bgr_from_file[channels * (y * m_bmp_info_header.width + x) + 2] = R;
		}
	}
}