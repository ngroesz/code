#!/usr/bin/ruby -w
require 'RMagick'

class Thumbnail
	
	def new(image_name, x, y, width, height)
	
		image = Image.read(image_name).first
		
		thumb_pix = image.export_pixels(x, y, width, height, "RGB")
		
		thumb = Image.new(width, height)
		thumb.import_pixels(0, 0, width, height "RGB", thumb_pix)
		
		return thumb
	end
end
