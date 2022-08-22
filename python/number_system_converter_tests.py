#!/usr/bin/env python

__author__ = "c0d145"
__credits__ = ["c0d145"]
__license__ = "MIT"
__version__ = "1.0"
__maintainer__ = "c0d145"
__status__ = "Development"

import sys, os.path, re
import argparse
import unittest

bin_path = os.path.dirname(os.path.realpath(__file__))
lib_path = os.path.abspath(bin_path)
sys.path.insert(0, lib_path)

import number_system_converter

class NSCTestCase(unittest.TestCase):

	def setUp(self):
		mode = 'unittest'
		test_param = {
			'digits_code': '100100111010', 'basis_1': '2', 'basis_2': '10'
		}
		self.app = number_system_converter.NSC(mode, test_param)
	# Binary conversion test cases
	def test_bin2oct(self):
#		self.assertEqual(self.app.convert('100100111010','2','8'), '4472')
		self.assertEqual(self.app.convert('1010111111111110','2','8'), '127776')
	def test_bin2dec(self):
		self.assertEqual(self.app.convert('100100111010','2','10'), '2362')
	def test_bin2hex(self):
		self.assertEqual(self.app.convert('100100111010','2','16'), '93A')
	# Octal conversion test cases
	def test_oct2bin(self):
		self.assertEqual(self.app.convert('666','8','2'), '110110110')
	def test_oct2dec(self):
		self.assertEqual(self.app.convert('666','8','10'), '438')
	def test_oct2hex(self):
		self.assertEqual(self.app.convert('666','8','16'), '1B6')
	# Decimal conversion test cases
	def test_dec2bin(self):
		self.assertEqual(self.app.convert('2352','10','2'), '100100110000')
	def test_dec2oct(self):
		self.assertEqual(self.app.convert('2352','10','8'), '4460')
	def test_dec2hex(self):
		self.assertEqual(self.app.convert('2352','10','16'), '930')
	# Hexadecimal conversion test cases
	def test_hex2bin(self):
		self.assertEqual(self.app.convert('AFFE','16','2'), '1010111111111110')
	def test_hex2oct(self):
		self.assertEqual(self.app.convert('AFFE','16','8'), '127776')
	def test_hex2dec(self):
		self.assertEqual(self.app.convert('AFFE','16','10'), '45054')

	# Testing for invalid format
	def test_convert(self):
		self.assertEqual(self.app.convert('178k','16','2'), self.app.NON_VALID)
		self.assertEqual(self.app.convert('Operator','10','2'), self.app.NON_VALID)

	def tearDown(self):
		pass
		#print('Test done.')

if __name__ == '__main__':
	unittest.main()
