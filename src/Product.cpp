#include "Product.h"

 Product::Product(int id, int quantity, int volume) {
     this->id = id;
     this->quantity = quantity;
     this->volume = volume;
 }

 int Product::getId() {
     return this->id;
 }

 int Product::getQuantity() {
     return this->quantity;
 }

 int Product::getVolume() {
     return this->volume;
 }