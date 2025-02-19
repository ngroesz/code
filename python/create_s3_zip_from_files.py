from zipfile import ZipFile
from botocore.exceptions import ClientError
from io import BytesIO
import os
import boto3

s3_bucket = 'session-data-files-cd824410'

keys = [
    'road.jpg',
    'moto.jpg',
    'sunset.jpg'
]

archive_path = 'session_data_file_archive'

archive = BytesIO()

s3_client = boto3.client(
        's3',
        region_name='us-west-2',
        aws_access_key_id='<ACCESS_KEY>',
        aws_secret_access_key='<SECRET_KEY>'
    )

with ZipFile(archive, 'w') as zip_archive:
    for key in keys:
        s3_response = None
        try:
            s3_response = s3_client.get_object(Bucket=s3_bucket, Key=key)
        except ClientError as e:
            print(e)

        out_filename = os.path.join(archive_path, key)
        with zip_archive.open(out_filename, 'w') as outfile:
            outfile.write(s3_response['Body'].read())

archive.seek(0)

try:
    response = s3_client.put_object(
        Body=archive.read(),
        Bucket='test-grm-zip',
        Key='session_data_file_archive.zip',
    )
except ClientError as e:
    print(e)
