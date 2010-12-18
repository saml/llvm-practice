This is LLVM practice

# Install LLVM

    mv ~/Downloads/clang-2.8 ~/Downloads/llvm-2.8/tools/clang
    cd ~/Downloads/llvm-2.8
    ./configure --prefix=~/opt/llvm
    make -j 12
    make install

# Or, try scripts/llvm-build.sh

    scripts/llvm-build.sh ~/opt ~/Downloads/llvm-2.8 ~/Downloads/clang-2.8

note that it builds with `-DCMAKE_BUILD_TYPE=Debug`. It's 1.7G!!
Maybe try with `-DBUILD_SHARED_LIBS`.
More cmake info at http://llvm.org/docs/CMake.html .

# Set up Vim

    cd ~/opt/llvm
    ctags -R --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ $HOME/opt/llvm/include
    mv tags ~/.vim/tags/llvm

# Edit ~/.vimrc

    "au BufAdd,BufNewFile * nested tab sball
    set tags+=~/.vim/tags/llvm
    nmap <C-\> :tab split<CR>:normal evBy<CR>:exec "tag " . @"<CR>

# Build Project

    cd llvm-practice
    mkdir build
    cmake -DLLVM_HOME=$HOME/opt/llvm -G 'Unix Makefiles' ..
    make

# Set up Eclipse CDT4 Project

    mkdir ~/workspace/llvm-practice-eclipse
    cd ~/workspace/llvm-practice-eclipse
    cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DLLVM_HOME=$HOME/opt/llvm ../llvm-practice

and open eclipse, Import > Existing Project... select ~/workspace/llvm-practice-eclipse
(uncheck Copy files to workspace..)
Detailed instruction is here: http://www.cmake.org/Wiki/CMake:Eclipse_UNIX_Tutorial

