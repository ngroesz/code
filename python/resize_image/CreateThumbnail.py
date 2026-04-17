import boto3
import os
import sys
import uuid
from PIL import Image
import PIL.Image

THUMBNAIL_WIDTH = 128
THUMBNAIL_HEIGHT = 128

s3_client = boto3.client('s3')

def resize_image(image_path, resized_path):
    with Image.open(image_path) as image:
        image.thumbnail((THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT))
        image.save(resized_path, image.format)

def handler(event, context):
    keys_created = []

    for record in event['Records']:
        bucket = record['s3']['bucket']['name']
        key = record['s3']['object']['key']
        download_path = '/tmp/{}{}'.format(uuid.uuid4(), key)
        upload_path = '/tmp/{}-resized'.format(key)

        s3_client.download_file(bucket, key, download_path)
        resize_image(download_path, upload_path)
        thumbnail_key = '{}-resized'
        s3_client.upload_file(upload_path, '{}-resized'.format(bucket), thumbnail_key)
        keys_created.append(thumbnail_key)


    return {'message': 'resized images: '.format(', '.join(keys_created))}


