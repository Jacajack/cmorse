../bin/cmorse -i test.txt -o morse
../bin/cmorse -d -i morse -o text
if ! cmp test.txt text
then
echo "Files are not the same!"
fi
rm -f morse text
