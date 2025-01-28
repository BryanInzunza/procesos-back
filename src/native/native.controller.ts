import { Controller, Get, Param } from '@nestjs/common';
import { NativeService } from './native.service';

@Controller('native')
export class NativeController {
    constructor(private readonly nativeService: NativeService) { }

    @Get('start')
    startLoops(): string {
        return this.nativeService.startLoops();
    }

    @Get('iteration/:loopNumber')
    getIteration(@Param('loopNumber') loopNumber: string): string {
        const loopNum = parseInt(loopNumber, 10); // Convertir a número entero
        if (isNaN(loopNum)) {
            throw new Error('Invalid loop number');
        }
        return this.nativeService.getIteration(loopNum);
    }
}