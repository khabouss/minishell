#!/bin/sh

goinfre="/goinfre/$(whoami)"
rm -rf $HOME/.brew
mkdir -p $goinfre/.brew
ln -s $goinfre/.brew ~/.brew
git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew
echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc
echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.bashrc && source $HOME/.bashrc
brew update

brew install readline
