#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <thread> 
#include <stdlib.h>
#include <fstream>
#include <Windows.h>
#include <Windows.h>

class Image
{
public:
	int width;
	int height;
	int ROI;
	int* refCount;
	int channels;
	uint8_t* data;

	//defult c'tor
	Image()
	{
		refCount = new int;
		data = nullptr;
	}

	//c'tor
	Image(int w, int h, int c, std::vector<uint8_t> const& _data = {})
	{
		if (c != 1 && c != 3)
			throw std::exception("The channels must be 1 or 3");
		if (w < 1 || h < 1)
			throw std::exception("the arguments are invalid");
		width = w;
		height = h;
		channels = c;
		refCount = new int;
		*refCount = 1;
		ROI = width;
		data = new uint8_t[(w * 2) * h * c];
		if (!_data.empty())
			memcpy(data, _data.data(), (width + 2) * height * channels);
	}

	//view c'tor
	Image(Image const& other, int tl_x, int tl_y, int ROI_width, int ROI_height)
	{
		if (tl_x<0 || tl_y + ROI_width > other.ROI || tl_y<0 || tl_x + ROI_height>other.height)
			throw std::invalid_argument("Bad view image dimension");
		width = ROI_width;
		height = ROI_height;
		ROI = other.ROI;
		channels = other.channels;
		data = other.data + tl_x * ROI + tl_y;
		refCount = (other.refCount);
		(*refCount)++;
	}

	//copy c'tor
	Image(Image const& other)
		:width(other.width), height(other.height), ROI(other.ROI), channels(other.channels)
	{
		data = other.data;
		refCount = (other.refCount);
		(*refCount)++;
	}

	//move c'tor
	Image(Image&& other)noexcept :
		width(other.width), height(other.height), ROI(other.ROI), channels(other.channels)
	{
		data = other.data;
		other.data = nullptr;
		refCount = (other.refCount);
		other.refCount = nullptr;
	}

	//d'tor
	~Image()
	{
		if (refCount)
		{
			if (*refCount == 1)
			{
				delete refCount;
				delete[] data;
			}
			else
				(*refCount)--;
		}
	}


	static Image readImage(std::string filename);

	static void DisplayImage(const Image& img);

	static void writeImage(const std::string& filename, const Image& image);


	void copy/*AndWrite*/(Image img);

	void copy2/*AndWrite*/(Image img);

	static void waitKey(int delay = 0);

	std::tuple<int, int> getSize();


	std::vector<uint8_t> getAllPixel(int i, int j) const;
	uint8_t& getPixelCH(int i, int j, int c);
	void setAllPixel(int i, int j, const std::vector<uint8_t>& pixel);
	void setPixelCH(int i, int j, int c, int value);


	bool empty();

	Image clone()const;

	std::vector<std::vector<uint8_t>>splitChannels()const;

	std::vector<uint8_t>getData();

	uint8_t at(int i, int j, int c);

	std::vector<uint8_t> at(int i, int j);


	uint8_t* ptr(int i);

	uint8_t* ptr(int i, int j);

	uint8_t* ptr(int i, int j, int c);


	Image operator=(Image const& other);

	uint8_t& operator()(int i, int j, int c);

	Image operator +(uint8_t value) const; // by element

	Image operator -(uint8_t value) const; // by element

	bool operator ==(Image const& other) const; // compare by element to other image

	bool operator ==(uint8_t const& value) const; // compare all elements to value

};

