# coding:utf-8
from selenium import webdriver
import time
driver = webdriver.PhantomJS(executable_path="C:\Python27\Scripts\phantomjs.exe")
driver.get('https://www.baidu.com')
elem = driver.find_element_by_id('kw')
elem.send_keys(u'php')
driver.find_element_by_id('su').click()
driver.refresh()
#print('ҳ����⣺', driver.title)
#print(driver.current_url)
try:
	driver.save_screenshot('11.png')
except Exception as e:
	print e
time.sleep(1)
driver.quit()
#print('�������ҳ��Դ�룺\n', driver.page_source)