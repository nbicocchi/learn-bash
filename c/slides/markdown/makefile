CC=pandoc
FLAGS_SLIDES=--from markdown --to beamer --template "eisvogel.tex" --listings
FLAGS_BOOK=--from markdown --template "eisvogel.tex" --listings
PDFDIR=../pdf
SOURCE_FILES=$(wildcard *.md)
OBJECT_FILES=$(SOURCE_FILES:%.md=$(PDFDIR)/%.pdf)

all: $(OBJECT_FILES)


clean:
		rm -rf $(PDFDIR)/*.pdf

$(PDFDIR)/%.pdf: %.md
		$(CC) $< -o $@ $(FLAGS_SLIDES)
