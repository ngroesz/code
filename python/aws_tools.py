import re
import os
import boto

from common.common import *
from boto.s3.connection import S3Connection, Location
from boto.s3.key import Key

class AwsTools:
    def __init__(self, config_filename):
        self.config = load_config(config_filename)
        self.rs_connection = connect_db(self.config)
        self.rs_cursor = self.rs_connection.cursor()

    def upload_to_s3(self, filename, bucket_path, subdirectory_bucket_path):
        s3_conn = S3Connection(self.config['aws']['access_key_id'], self.config['aws']['secret_access_key'])
        s3_bucket = s3_conn.create_bucket(bucket_path)

        k = s3_bucket.new_key(subdirectory_bucket_path + '/' + os.path.basename(filename))
        k.set_contents_from_filename(filename)

        k.close()
        s3_conn.close()

    def copy_into_table_from_local_file(self, tablename, filename, options={}):
        bucket_path = 'tmp-table-load-dir'
        s3_conn = S3Connection(self.config['aws']['access_key_id'], self.config['aws']['secret_access_key'])

        s3_bucket = s3_conn.get_bucket(bucket_path)

        key_name = os.path.basename(filename)

        key = s3_bucket.get_key(key_name)
        if not key:
            key = s3_bucket.new_key(key_name)

        key.set_contents_from_filename(filename)

        key.close()
        s3_conn.close()

        query = "copy {0} ".format(tablename)

        if 'fields' in options: 
            query += "({0})".format(','.join(options['fields']))

        query += " from 's3://{0}/{1}' credentials 'aws_access_key_id={2};aws_secret_access_key={3}' CSV region '{4}' GZIP".format(
            bucket_path, key_name, self.config['aws']['access_key_id'], self.config['aws']['secret_access_key'], Location.USWest2
        )

        if 'delimiter' in options:
            query += ' delimiter \'' + options['delimiter'] + '\''

        try:
            self.rs_cursor.execute(query)
            self.rs_connection.commit()
        except Exception as e:
            print ('Unable to load file ' + filename + ' into table ' + tablename + '(' + e.pgerror + ')')
            raise

        if 'preserve_s3_key' not in options or options['preserve_s3_key'] != 1:
            s3_bucket.delete_key(os.path.basename(filename))

    def close(self):
        self.rs_connection.close()
