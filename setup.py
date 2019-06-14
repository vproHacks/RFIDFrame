import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()
setuptools.setup(
     name='RFIDFrame',
     version='0.01',
     scripts=['RFIDFrame'] ,
     author="Vraj Prajapati",
     author_email="blahthing8@gmail.com",
     description="A Framework to use RFID Devicec",
     long_description=long_description,
     long_description_content_type="text/markdown",
     url="https://github.com/vproHacks/RFIDFrame",
     packages=setuptools.find_packages(),
     classifiers=[
         "Programming Language :: Python :: 3",
         "Operating System :: OS Independent",
     ],
 )