cd doc

for f in *.md; do
  md2man-roff ./"$f" > ../man/"${f%.md}"
done

cd ../man
