from selenium import webdriver
obj = webdriver.PhantomJS(executable_path="C:\Python27\Scripts\phantomjs.exe")
obj.set_page_load_timeout(5)
#obj.maximize_window()
#obj.set_window_size('480','800')
try:
	obj.get('http://www.baidu.com')
	obj.save_screenshot('11.png')
except Exception as e:
	print e