if(verifyCorrectness(head) == 0){
    //     pNode actual = head->first;
    //     while(actual!=NULL){
    //         if(actual->value>0){
    //             int k = searchMap(levels, n, actual->value); // Verify is actual->value is already in the map
    //             if(k!=-1){ // if so:
    //                 int x = sublevels(head, actual); 
    //                 if(x>levels[k].data){ // Verify which one has the bigger number of direct sublevels
    //                     levels[k].data = x;
    //                 }
    //             }
    //             else{
    //                 levels[i].label = actual->value;
    //                 levels[i].data = sublevels(head, actual);
    //                 i++;
    //             }
    //         }
    //         actual = actual->next;
    //     }
    //     insertionSort(levels, i);
    //     printMap(levels, i);
    // }
    // else{
    //     printf("sequencia invalida.");
    //     return 0;
    // }