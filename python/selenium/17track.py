# coding:utf-8
from selenium import webdriver
import time
driver1 = webdriver.PhantomJS(executable_path="C:\Python27\Scripts\phantomjs.exe")
driver1.get('https://www.17track.net/zh-cn/track?nums=LM413299111CN&fc=0')
#elem = driver1.find_element_by_id('CodeMirror-line').send_keys('pan123322432')
#driver1.find_element_by_xpath("//em[contains(text(),'Track')]").click()
#elem=driver1.find_element_by_xpath("//pre[@class='CodeMirror-placeholder']")
#print ('hello:',elem.text)
#elem.send_keys('pan123322432');
elem=driver1.find_element_by_xpath('//time')
elemnew=driver1.find_element_by_xpath("//span[@class='newest']")
#print elemnew.text()
#elem.send_keys(u'php')
#driver1.find_element_by_id('su').click()
#driver1.refresh()
#print('页面标题：', driver.title)
#print(driver.current_url)
try:
	print ('hello',elemnew.text)
	print ('hello',elem.text)
	#driver1.save_screenshot('15.png')
except Exception as e:
	print e
time.sleep(1)
driver1.quit()
#print('搜索后的页面源码：\n', driver.page_source)