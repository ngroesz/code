#!/usr/bin/ruby -w

require 'RMagick'
require 'image_dev.rb'

THUMB_WIDTH = 200
THUMB_HEIGHT = 200
PIXEL_STEP = 5


def thumbnail(image_name, x, y, width, height)
	
	image = Magick::Image.read(image_name).first
		
	thumb_pix = image.export_pixels(x, y, width, height, "RGB")
		
	thumb = Magick::Image.new(width, height)
	thumb.import_pixels(0, 0, width, height, "RGB", thumb_pix)
		
	return thumb
end


Dir.foreach("images") { |file|
	if file =~ /5\.(jpg|jpeg)/i then
		
		img = ImageDev.new('images/' + file)

		x, y = img.analyze(THUMB_WIDTH, THUMB_HEIGHT, PIXEL_STEP)

		puts "x = #{x}. y = #{y}"

		thumb = thumbnail('images/' + file, x, y, THUMB_WIDTH, THUMB_HEIGHT)
		
		thumb.write('thumbs/' + file)
	end
}


