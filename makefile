objects := main.o     
PREFIX := /usr/local/bin

default: install

install: tigger rubydeps
	@echo "Copying Tigger into /usr/bin"
	@echo "Please ensure the /usr/bin is in your path!"
	cp tigger $(PREFIX)
	@echo "Finished. Tigger is installed. Type 'tigger' for usage."

rubydeps:
	@echo "Installing Ruby dependency Grit"
	@echo "Note that Ruby must be installed for this to work"
	gem install grit                                         

tigger : $(objects)
	@echo "Linking source files..."
	cc -o $@ $(objects)       

main.o : main.c tigger_util.h
	@echo "Installing Tigger....."
	cc -c main.c                     

clean :
	rm edit $(objects)