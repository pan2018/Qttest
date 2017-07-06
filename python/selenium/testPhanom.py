# -*- coding: utf-8 -*-
from selenium import webdriver
import time
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
dcap = dict(DesiredCapabilities.PHANTOMJS)
dcap["phantomjs.page.settings.userAgent"] = ("Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.221 Safari/537.36 SE 2.X MetaSr 1.0") #����user-agent����ͷ
dcap["phantomjs.page.settings.loadImages"] = False #��ֹ����ͼƬ
driver = webdriver.PhantomJS(desired_capabilities=dcap)
driver.set_page_load_timeout(80) #����ҳ�������ʱ��Ϊ40s

def phantomjs_req(url):
	#ʹ���ַ�����ȡ�Դﵽɾ��windows�ļ��еĻ��з�Ŀ�ģ���ȡ�ַ�����ͷ��������һ���ַ�
	url_t = '%s%s%s'%("https://www.17track.net/zh-cn/track?nums=",url[:-1],"&fc=0")
	driver.get(url_t)
	#��ӡ��ǰurl
	print driver.current_url

#��ȡ�ļ��еĵ���
with open('shipp.txt','r') as f:
	url_pan=f.readlines()

#ѭ�����ü�����ҳ������ȡ��Ҫ��Ϣ
while len(url_pan)>0:
	time.sleep(5)
	print len(url_pan)
	for i in url_pan:
		time.sleep(1)
		phantomjs_req(i)
		time.sleep(2)
		driver.get_screenshot_as_file('%s,%s'%('09','.png')) #������ҳ��ͼ
		try:
			#elem=driver.find_element_by_xpath('//time')
			#elemnew=driver.find_element_by_xpath("//span[@class='newest']")
			elempan=driver.find_element_by_xpath("//dd[@class='new']")
			with open('panjf.txt','a+') as f:
				f.write(elempan.text)
				f.write('\n')
			print ('elempan',elempan.text.encode('utf-8'))
			#print ('elem',elem.text)
			url_pan.remove(i)
		except Exception as e:
			print e
			continue
driver.quit() #�˳������