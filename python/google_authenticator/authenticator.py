import time
import pyotp
import qrcode


#key = pyotp.random_base32()
key = 'THSUVG4DVB4SQT4QEVBU7VTOVMBUMPDV'
totp = pyotp.totp.TOTP(key)


uri = totp.provisioning_uri(
    name='user_name_here',
    issuer_name='OHSU AIMS Lab',
    )

print(uri)
qrcode.make(uri).save("qr.png")


verify_totp = pyotp.totp.TOTP(key)

# verifying the code
while True:
  print(verify_totp.now())
  print(verify_totp.verify(input(("Enter the Code : "))))
