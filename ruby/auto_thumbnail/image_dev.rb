#!/usr/bin/ruby -w
require 'RMagick'

class ImageDev
	SAMPLE_WIDTH = 100;
	SAMPLE_HEIGHT = 100;
	PIXEL_STEP = 3;
	
	
	def initialize(image_name)
		@image = Magick::Image.read(image_name).first
	end
	
	def analyze(sample_width = SAMPLE_WIDTH, sample_height = SAMPLE_HEIGHT, pixel_step = PIXEL_STEP)
		@sample_width = sample_width
		@sample_height = sample_height
		@pixel_step = pixel_step
		
		columns = (@image.columns / @sample_width).to_i
		rows = (@image.rows / @sample_height).to_i
	
		highest_dev = 0;
		highest_dev_x = nil;
		highest_dev_y = nil;
		
		for c in 0...columns
			for r in 0...rows
				x = c * @sample_width
				y = r * @sample_height
				avg = sample(x, y, @sample_width, @sample_height)
				
				total_dev = avg['red'] + avg['green'] + avg['blue']
						
				if total_dev > highest_dev then
					highest_dev = total_dev
					highest_dev_x = x
					highest_dev_y = y
				end
			end
		end
		
		return highest_dev_x, highest_dev_y
	end
	
	def pixel_rgb(pixel)
		color = {'red' => 0, 'green' => 0, 'blue' => 0}
	
		color['red'] = pixel.red >> 8
		color['blue'] = pixel.blue >> 8
		color['green'] = pixel.green >> 8
		return color
	end
	
	def standard_deviation(values)
		total = 0
		
		values.each do |v|
			total = total + v
		end
		mean = total / values.length
	
	
		std_total = 0
		values.each do |v|
			var = v - mean
			std_total = std_total + (v - mean)**2
		end
		
		return Math.sqrt(std_total/(values.length - 1))
	end
		
	def sample(x_start, y_start, width, height)
		sample_avg = {'red' => 0, 'green' => 0, 'blue' => 0}
		
		x_end = x_start + width > @image.columns ? @image.columns : x_start + width;
		y_end = y_start + height > @image.rows ? @image.rows : y_start + height;
			
		red_values = Array.new();
		green_values = Array.new();
		blue_values = Array.new();
		
		x_start.step(x_end, @pixel_step) { |x|
			y_start.step(y_end, @pixel_step) { |y|
				color = pixel_rgb(@image.pixel_color(x, y))
				red_values.push(color['red'])
				green_values.push(color['green'])
				blue_values.push(color['blue'])
			}
		}
		
		sample_avg['red'] = standard_deviation(red_values).to_i
		sample_avg['green'] = standard_deviation(green_values).to_i
		sample_avg['blue'] = standard_deviation(blue_values).to_i
		return sample_avg
	end
end

