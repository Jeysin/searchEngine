testRssParse.out:testRssParse.cpp
	g++ testRssParse.cpp ../src/RssParse.cpp ../src/GlobalVariable.cpp ../src/tinyxml2.cpp ../src/int2str.cpp ../src/GetFilenameFromDir.cpp ../src/ReadConfigFile.cpp ../src/Mylog.cpp -o rssParse.out -pthread -llog4cpp -std=c++11
#	g++ testReadByOffset.cpp ../src/ReadConfigFile.cpp ../src/StopWordDict.cpp ../src/Mylog.cpp ../src/int2str.cpp -o readByOff.out -llog4cpp -pthread -std=c++11
#	g++ testRmRepeat.cpp ../src/Mylog.cpp ../src/int2str.cpp ../src/ReadConfigFile.cpp ../src/RmRepeat.cpp -o rmRepeat.out -llog4cpp -pthread -std=c++11
#	g++ testCppjieba.cpp ../src/StopWordDict.cpp ../src/Mylog.cpp ../src/ReadConfigFile.cpp ../src/int2str.cpp -o jieba.out -llog4cpp -pthread -std=c++11
#	g++ testInvertIndex.cpp ../src/InvertIndex.cpp ../src/StopWordDict.cpp ../src/Mylog.cpp ../src/ReadConfigFile.cpp ../src/GlobalVariable.cpp ../src/int2str.cpp -o invertIndex.out -llog4cpp -pthread -std=c++11
#	g++ testWebQuery.cpp ../src/WebQuery.cpp ../src/Mylog.cpp ../src/ReadConfigFile.cpp ../src/int2str.cpp ../src/GlobalVariable.cpp -o webQuery.out -llog4cpp -pthread -ljson -std=c++11
.PHONY:clean
clean:
	rm rssParse.out
#	rm readByOff.out
#	rm rmRepeat.out
#	rm jieba.out
#	rm invertIndex.out
#	rm webQuery.out 
