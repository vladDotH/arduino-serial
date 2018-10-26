

	Небольшая библиотека для управления Arduino - й посредством Bluetooth или прямого подключения по Usb.
	Позволяет управлять моторами, подключенными к Arduino.

	Порядок установки и использования : 

	1) подключить к проекту файлы motor.h и motor.cpp. В них содержится объектное представление моторов, по умолчанию
		моторы A и B на 4, 5 и 6, 7 пины на ардуине соответственно, что установить свои моторы на другие пины 
		потребуется в файле motor.срр его написать. Например: 	
		
		motor NAME ( #mainPin, #reversePin );
		
		или 	
		
		motor NAME = motor( #mainPin, #reversePin );

 	где #mainPin и #reversePin это пин для управляющего воздействия и пин для направления соответсвенно. mainPin желательно с Шим регуляцией
	чтобы на него делался analogWrite( #mainPin, #val );

	так же написать в файле motor.h :

	extern motor NAME;
	
	по образцу с моторов А и В. Такое объявление нужно, чтобы компилятор не ругался на объявление объектов в заголовочном файле. 
	Можно поэкспериментировать, но у меня ( CodeBlocks 17.12 и дефолтный компилятор minGW ) вылетала |error: ld returned 1 exit status|,
	если просто написать 	

	motor NAME ( #mainPin, #reversePin );		

	в motor.h .
	
	2) В зависимости от  ОС подключить к проэкту файлу wincom.h и wincom.cpp на Windows.
	   Или nixcom.h и nixcom.cpp на Linux .

	3) Использовать где нужно:
	   Объявить контроллер - winController или nixController. В аргументах указать порт ( #port ).
	   У windows это будет всегда ComPort, поэтому нужно только его узнать и написать нормер. 
	   С linux посложнее. Он может называться по разному. Для этого нужно посмотреть к какому порту Arduino включено.
	   У меня это был /dev/ttyACM0

	   Далее Можно напрямую управлять мотором через метод

	   #controllerName . motorStart( #motorName, #value );

		Либо же можно подключить два мотора для езды
		
		#controllerName . setLR ( &leftMotorName, &rightMotorName );														
		
		Передав указатели на моторы. И далее управлять ими
		
		#controllerName . ride ( #lVal, #rVal );


	4) Залить скетч ardPart.cpp на Arduino.

	Работоспособность проверялась на Arduino uno, Windows и на Orange Pi plus 2 с OC Armbian.

