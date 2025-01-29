import { Controller, Get, Param } from '@nestjs/common';
import { NativeService } from './native.service';

@Controller('native')
export class NativeController {
  constructor(private readonly nativeService: NativeService) {}

  @Get('startLoops')
  startLoops(): string {
    return this.nativeService.startLoops();
  }

  @Get('iteration/:loopNumber')
  getIteration(@Param('loopNumber') loopNumber: string): string {
    const loopNum = parseInt(loopNumber, 10); // Convertir a número
    if (isNaN(loopNum)) {
      throw new Error('A number was expected');
    }
    return this.nativeService.getIteration(loopNum);
  }

  @Get('pids')
  getPIDs(): number[] {
    return this.nativeService.getPIDs();
  }
}