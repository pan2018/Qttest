# coding:utf-8
from selenium import webdriver
import time
driver1 = webdriver.PhantomJS(executable_path="C:\Python27\Scripts\phantomjs.exe")
driver1.get('http://www.shpostwish.com/tracking')
elem = driver1.find_element_by_id('search-tracking').send_keys(u'RS866344119NL')
driver1.find_element_by_id('abc').click()
time.sleep(1)
searchresult=driver1.find_element_by_id('search-result-header')
print('ҳ����⣺', searchresult.text)
#find_element_by_xpath("//input[contains(text(),'�����ѯ')]").click()
#driver1.find_element_by_xpath("//em[contains(text(),'Track')]").click()
#elem=driver1.find_element_by_xpath("//pre[@class='CodeMirror-placeholder']")

#driver1.refresh()
pan = driver1.find_element_by_id('search-tracking')
print('ҳ����⣺', driver1.title)
#print(driver.current_url)
try:
	print ('hello',pan.text)
	#find_element_by_xpath("//input[contains(text(),'�����ѯ')]").click()
	#driver1.save_screenshot('15.png')
except Exception as e:
	print e
time.sleep(1)
driver1.quit()
#print('�������ҳ��Դ�룺\n', driver.page_source)


 #response.xpath('/html/body/div[4]/table/tr/td/table/tr[2]/td/table/tr/td[1]/table/tr/td/div[3]/form/input[4]').extract()