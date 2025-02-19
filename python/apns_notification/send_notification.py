import sys
from collections import namedtuple

from apns2.client import APNsClient
from apns2.payload import Payload
from apns2.credentials import TokenCredentials


Notification = namedtuple('Notification', ['token', 'payload'])


def main():
    token_hex = 'df278343d243dd2cd4352c9f3e3afb75df1f70af1486585d07b0e624d31d66f1'
    payload = Payload(alert="Hello World!", sound="default", badge=1)
    topic = 'edu.ohsu.dose'

    # To send multiple notifications in a batch
    notifications = [Notification(payload=payload, token=token_hex)]

    auth_key_path = './AuthKey_X3PAHGQCT2.p8'
    auth_key_id = 'ZJJ4G4TA5Y'
    team_id = 'ZA685R3CWP'
    token_credentials = TokenCredentials(auth_key_path=auth_key_path, auth_key_id=auth_key_id, team_id=team_id)
    client = APNsClient(credentials=token_credentials, use_sandbox=True)
    print(client.send_notification_batch(notifications=notifications, topic=topic))


if __name__ == '__main__':
    main()
