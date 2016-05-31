touch testlog.log
../bin/cmorse -i test.txt -o morse
../bin/cmorse -d -i morse -o text
if ! cmp test.txt text
then
echo "Files are not the same!" >> testlog.log
fi
#Before deleting files log their content
cat test.txt >> testlog.log
echo "<<<<>>>>" >> testlog.log
cat morse >> testlog.log
echo "<<<<>>>>" >> testlog.log
cat text >> testlog.log

if pastebinit -h
then
	pastebinit -i testlog.log
fi

rm -f morse text testlog.txt
