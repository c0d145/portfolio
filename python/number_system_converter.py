#!/usr/bin/python

__author__ = "c0d145"
__credits__ = ["c0d145"]
__license__ = "MIT"
__version__ = "1.0"
__maintainer__ = "c0d145"
__status__ = "Development"

import sys, os.path, re
import argparse
import unittest

"""
This code implements an number system converter for dual, octal, decimal and hex numbers.
I coded this just for fun while taking a computer architecture course to play around with
Python while utilizing the unit testing framework. 
"""
class NSC():
	# Statics for Exit-Codes
	EXIT_PASS, EXIT_FAIL = 0, 1
	NON_VALID = "Argument 1 has invalid format"
	basis = ["2","8","10","16"]
	digits = []

	def __init__(self, mode = 'normal', test_param = None):
		# Validate and process argument options
		self.parse_args(mode, test_param)

	def parse_args(self, mode, test_param):
		if mode == 'unittest':
			if test_param is None:
				print("Missing test param")
				self.app_exit('fail')

#			self.name = test_param['app_name']
#			self.verbose = test_param['verbose']
			self.digits_code = test_param['digits_code'] 
			self.basis_1 = test_param['basis_1']
			self.basis_2 = test_param['basis_2']
		else:
			#print ("Number of arguments:" + str(len(sys.argv)))
			#print ("Argument List:" + str(sys.argv))

			# create parser
			parser = argparse.ArgumentParser()
			parser = argparse.ArgumentParser(description='Number System Converter: For binary, octal, decimal, hexa numbers')
			#parser.add_argument('-n', '--name', help='Name of myApp', required=True)
			#parser.add_argument('--verbose', action='store_true', help='Verbose mode with more information printed')

			# add arguments to the parser
			parser.add_argument("digits_code") 	# := Stellenocde von Basis_1
			parser.add_argument("basis_1")		# := Ausgangsbasis Basis_1
			parser.add_argument("basis_2")		# := Ausgangsbasis Basis_2
			 
			# parse the arguments
			args = parser.parse_args()

			#self.name = args.name
			#self.verbose = args.verbose
			self.digits_code = args.digits_code
			self.basis_1 = args.basis_1
			self.basis_2 = args.basis_2
			
			self.convert(self.digits_code, self.basis_1, self.basis_2)

		if not self.basis_1 in self.basis:
			print ("Base_1 is not valid. Must be 2,8,10 or 16. Given argument was: " + self.basis_1)
			sys.exit()
		elif not self.basis_2 in self.basis:
			print ("Base_2 is not valid. Must be 2,8,10 or 16. Given argument was: " + self.basis_2)
			sys.exit()
		elif (not self.is_validFormat(self.digits_code)):
			print ("Argument 1 is not in a valid format: " + self.digits_code )
			sys.exit()

#			elif (not self.is_bin(self.digits_code)):
#				print ("Argument 1 is not a binary number " + self.digits_code )
#			elif (not self.is_oct(self.digits_code)):
#				print ("Argument 1 is not a octal number" + self.digits_code )
#			elif (not self.is_dec(self.digits_code)):
#				print ("Argument 1 is not a Integer " + self.digits_code )
#			elif (not self.is_hex(self.digits_code)):
#				print ("Argument 1 is not a hexadecimal " + self.digits_code )
			
			

	def app_exit(self, status):
		if status.lower() == 'pass':
			print("** App Exit Status: PASS \n")
			exit(self.EXIT_PASS)
		elif status.lower() == 'skip':
			print("** App Exit Status: SKIP \n")
			exit(self.EXIT_PASS)
		else:
			print("** App Exit Status: FAIL \n")
			exit(self.EXIT_FAIL)

#	def get_app_name(self):
#		return self.name

	def is_bin(self,s):
		try:
			int(s, 2)
			return True
		except ValueError:
			return False

	def is_oct(self,s):
		try:
			int(s, 8)
			return True
		except ValueError:
			return False

	def is_dec(self,s):
		try:
			int(s, 10)
			return True
		except ValueError:
			return False

	def is_hex(self,s):
		try:
			int(s, 16)
			return True
		except ValueError:
			return False

	def is_validFormat(self, s):
		return (self.is_bin(s) or self.is_oct(s) or self.is_dec(s) or self.is_hex(s))
	

	# Function to convert from binary to decimal number system.
	def bin2dec(self,digits):
		result=0
		for x in digits:
			result = result*2+int(x)
		return result

	# Function to convert from binary to octal number system.
	def bin2oct(self,number):
		q, remainder = divmod(len(number), 3)
		number = number.zfill(len(number)+(3-remainder))
		result=""
		n = 3
		chunks = [number[i:i+n] for i in range(0, len(number), n)]
		for x in chunks:
			# I'm using the oct()-function here to save my the work of a lookup table.
			result += oct(int(x, 2))[2:]
		return result
			
	# Function to convert from binary to hexadecimal number system.
	def bin2hex(self,number):
		result=""
		n = 4
		chunks = [number[i:i+n] for i in range(0, len(number), n)]
		for x in chunks:
			# I'm using the hex()-function here to save my the work of a lookup table.
			result += hex(int(x, 2))[2:]
		return result.upper()

	# Function to convert from octal to binary number system.
	def oct2bin(self,digits):
		result=""
		for x in digits:
			# I'm using the oct()-function here to save my the work of a lookup table.
			result += str(bin(int(x, 8)))[2:]
		return result

	# Function to convert from octal to decimal number system.
	def oct2dec(self,digits):
		result=0
		for x in digits:
			result = result*8+int(x)
		return result

	# Function to convert from octal to hexadecimal number system.
	def oct2hex(self,digits):
		return self.dec2hex(self.oct2dec(digits))

	# Function to convert from decimal to binary number system.
	def dec2bin(self,number):
		result = ""
		while number != 0:
			number, digit = divmod(number, 2)
			result+=str(digit)
		return int(result[::-1])

	# Function to convert from decimal to binary number system.
	def dec2hex(self,number):
		result = ""
		while number != 0:
			number, digit = divmod(number, 16)
			# I'm using the hex()-function here to save my the work of a lookup table.
			#result+=str(hex(int(digit, 16))[2:])
			result+=str(hex(digit)[2:])
		#return int(result[::-1])
		return result[::-1].upper()

	# Function to convert from decimal to binary number system.
	def dec2oct(self,number):
		result = ""
		while number != 0:
			number, digit = divmod(number, 8)
			# I'm using the hex()-function here to save my the work of a lookup table.
			result+=str(oct(digit)[2:])
		return int(result[::-1])

	def hex2bin(self,number):
		result = ""
		for x in number:
			# I'm using the bin()-function here to save my the work of a lookup table.
			# .zfill fills up the converted number to 4 characters / digits.
			result += str(bin(int(x,16))[2:]).zfill(4)
		return result

	def hex2oct(self,number):
		return self.bin2oct(self.hex2bin(number))
		
	def hex2dec(self,digits):
		result=0
		for x in digits:
			result = result*16+int(x, 16)
		return result
	#	result = ""
	#	for x in number:
			# I'm using the bin()-function here to save my the work of a lookup table.
			# .zfill fills up the converted number to 4 characters / digits.
	#		result += str(oct(int(x,8))[2:]).zfill(3)
	#	return result

	def convert(self,digits_code,basis_1,basis_2):
		params = ("Given parameters: Digits code=" + digits_code + ", Basis_1=" + basis_1 + ", Basis_2=" + basis_2)
		# Every digit in the given digit code of base_1 has to be treated seperatley for the conversion.
		n = str(digits_code)
		digits = [str(x) for x in str(n)]
		# print(digits)
		result=""
		
		'''
		Cases for different base combinations
		'''
		if (basis_1 == basis_2):
			result=digits_code
		
		if(basis_1 == "2"):
			if(self.is_bin(digits_code)):
				if(basis_2 == "8"):
					result=str(self.bin2oct(digits_code))
				if(basis_2 == "10"):
					result=str(self.bin2dec(digits))
				if(basis_2 == "16"):
					result=str(self.bin2hex(digits_code))
			else:
				print ("Argument 1 is not a valid binary number " + digits_code )
				result=self.NON_VALID

		if(basis_1 == "8"):
			if(self.is_oct(digits_code)):
				if(basis_2 == "2"):
					result=str(self.oct2bin(digits))
				if(basis_2 == "10"):
					result=str(self.oct2dec(digits))
				if(basis_2 == "16"):
					result=str(self.oct2hex(digits))
			else:
				print ("Argument 1 is not a valid octal number " + digits_code )
				result=self.NON_VALID

		if(basis_1 == "10"):
			if(self.is_dec(digits_code)):
				if(basis_2 == "2"):
					result=str(self.dec2bin(int(digits_code)))
				if(basis_2 == "8"):
					result=str(self.dec2oct(int(digits_code)))
				if(basis_2 == "16"):
					result=str(self.dec2hex(int(digits_code)))
			else:
				print ("Argument 1 is not a valid decimal number " + digits_code )
				result=self.NON_VALID

		if(basis_1 == "16"):
			if(self.is_hex(digits_code)):
				if(basis_2 == "2"):
					result=str(self.hex2bin(digits_code))
				if(basis_2 == "8"):
					result=str(self.hex2oct(digits_code))
				if(basis_2 == "10"):
					result=str(self.hex2dec(digits_code))
			else:
				print ("Argument 1 is not a valid hexadecimal number " + digits_code )
				result=self.NON_VALID
		
		print(params + " Result: " + result)
		return(result)
		

'''
	class Tests(unittest.TestCase):
		def test(self):								  #test method
			self.assertEqual(bin2oct("100100111010"),"2362")
	if __name__=='__main__':
		unittest.main()
'''

if __name__ == '__main__':
	app = NSC()

