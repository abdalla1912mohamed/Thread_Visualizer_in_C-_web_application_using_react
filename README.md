# React + Vite

This template provides a minimal setup to get React working in Vite with HMR and some ESLint rules.

Currently, two official plugins are available:

- [@vitejs/plugin-react](https://github.com/vitejs/vite-plugin-react/blob/main/packages/plugin-react/README.md) uses [Babel](https://babeljs.io/) for Fast Refresh
- [@vitejs/plugin-react-swc](https://github.com/vitejs/vite-plugin-react-swc) uses [SWC](https://swc.rs/) for Fast Refresh
README 


Unzip and cd ThreadVisualizer directory 
cd back_end 
cd src 
rm -rf build 
mkdir build 
cd build 
cmake .. 
make 
cd bin 
./ws_example 
/////////// 
new Terminal  : 

ThreadVisualizer 
cd front_end 
cd src 
cd ThreadProfiler 
npm install 
npm run dev  

/////////
to run tests 
Unzip and cd ThreadVisualizer directory 
cd back_end 
cd src 
rm -rf build 
mkdir build 
cd build 
cmake .. 
make 
ctest  // run the corressponding  test files
